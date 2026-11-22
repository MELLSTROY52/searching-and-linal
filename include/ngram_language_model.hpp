#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <spellchecker.hpp>

#include "tokens.hpp"

class NgramLanguageModel {
private:

    std::unordered_map<std::string, std::size_t> unigram_counts;
    std::unordered_map<std::string, std::size_t> bigram_counts;
    std::unordered_map<std::string, std::size_t> trigram_counts;


    std::unordered_map<std::string, std::size_t> bigram_context_counts;
    std::unordered_map<std::string, std::size_t> trigram_context_counts;

    std::size_t total_words = 0;

public:

    void train(const std::vector<DocumentTokenize>& docs);

    NgramLanguageModel(const std::unordered_map<std::string , std::size_t>& vocab , std::size_t all_words) : unigram_counts(vocab) {
        for ( const auto& [ key, value] : vocab){
            total_words+= value;
        }
    }

    double probability_of_unigram(const std::string& word) const;

    double probability_of_bigram(const std::string& first_word,const std::string& second_word) const;

    double probability_of_trigram(const std::string& first_word,const std::string& second_word,const std::string& third_word) const;
};