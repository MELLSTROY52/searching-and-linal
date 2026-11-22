#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <spellchecker.hpp>

#include "tokens.hpp"
#include "ngram_language_model.hpp"

void NgramLanguageModel::train(const std::vector<DocumentTokenize>& docs) {

    for (std::size_t i = 0; i < docs.size(); i++) {
        const auto& tokens = docs[i].get_tokensContent();
        if (tokens.size() < 3) {
            continue;
        }
        for (std::size_t k = 0; k + 2 < tokens.size(); k++) {
            std::string word_for_gram;
            std::size_t j = k;
            word_for_gram += tokens[j] + " ";
            j++;
            word_for_gram += tokens[j];
            bigram_counts[word_for_gram]++;
            bigram_context_counts[tokens[k]]++;

            word_for_gram += " ";
            j++;

            word_for_gram += tokens[j];
            trigram_counts[word_for_gram]++;
            trigram_context_counts[tokens[k] + " " + tokens[k + 1]]++;
        }
    }
}

double NgramLanguageModel::probability_of_unigram(const std::string& word) const{
    if ( unigram_counts.find(word) != unigram_counts.end() ){
    return ( static_cast<double>(unigram_counts.at(word)) / total_words);
    }else{
        return 0;
    }
}

double NgramLanguageModel::probability_of_bigram(const std::string& first_word,const std::string& second_word) const{
        if (bigram_context_counts.find(first_word)!= bigram_context_counts.end() && 
        bigram_counts.find(first_word +  " " + second_word) != bigram_counts.end()){
            return ( static_cast<double>(bigram_counts.at(first_word + " " + second_word)) / static_cast<double>(bigram_context_counts.at(first_word)));
        }
        else{
            return 0;
        }
}

double NgramLanguageModel::probability_of_trigram(const std::string& first_word,const std::string& second_word,const std::string& third_word) const{
        if ( trigram_context_counts.find(first_word + " " + second_word) != trigram_context_counts.end() && 
         trigram_counts.find(first_word + " " + second_word + " " + third_word) != trigram_counts.end()){
            return ( static_cast<double>(trigram_counts.at(first_word + " " + second_word + " " + third_word)) / static_cast<double>(trigram_context_counts.at(first_word + " " + second_word)));
    }else{
        return 0;
    }
}