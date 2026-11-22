#include <advanced_spellchecker.hpp>
#include <algorithm>
#include <tokens.hpp>
#include <spellchecker.hpp>
#include <rapidfuzz/distance/Levenshtein.hpp>
#include <utility>
#include <unordered_map> 
#include <cstddef>

// std::size_t Levenshtein_func(std::string &query , std::string &word){
//     std::size_t n = query.size() +1;
//     std::size_t m = word.size() + 1;
//     std::vector<std::vector<std::size_t>>  matrix( n , std::vector<std::size_t>(  m, 0));

//     for ( std::size_t i = 0; i  < n; i++){
//         for ( std::size_t j = 0; j < m; j++){
//             if ( i == 0 || j ==0 ){
//                 matrix[i][j] = std::max( i , j);
//             }else{
//                 if ( query[i -1] == word[j -1]){
//                     matrix[i][j] = matrix[i-1][j-1];
//                 }else{
//                     matrix[i][j] = std::min({matrix[i-1][j-1] +1, matrix[i][j-1] +1, matrix[i-1][j]+1});
//             }
//         }
//     }
// }
// return matrix[n-1][m-1];
// }
// std::size_t distance = rapidfuzz::levenshtein_distance(key, corrected_query[i])

std::vector <std::vector<std::string>> Advanced_choice::most_suitable_candidates_from_lenven(std::vector<std::string>& query) { 
    std::vector <std::vector<std::string>> candidates;
    for ( std::size_t i = 0; i < query.size(); i++ ){
        std::vector<std::string> words_for_candi;
        words_for_candi.push_back(query[i]);
        for ( const auto&[key , value] : vocabulary.get_Vocabulary()){
                std::size_t distance = rapidfuzz::levenshtein_distance(key, query[i]);
                if ( distance <=2 ){
                    words_for_candi.push_back(key);
                }
            }
            candidates.push_back(words_for_candi);
        }
    return candidates;
}

std::string Advanced_choice::the_best_choice_from_candidates(std::vector<std::vector<std::string>>& candidates, Interpolation& inter,NgramLanguageModel& probabl,const std::vector<DocumentTokenize>& docs,const std::vector<std::string>& query) {
    std::string correct_query;
    std::vector<std::string> corrected_words;

    probabl.train(docs);

    for (std::size_t i = 0; i < candidates.size(); i++) {

        std::string best_word = query[i];
        double best_probability = -1.0;

        for (std::size_t j = 0; j < candidates[i].size(); j++) {

            const std::string& candidate = candidates[i][j];

            double unigram = probabl.probability_of_unigram(candidate);

            double bigram = 0.0;
            double trigram = 0.0;

            if (i >= 1) {
                bigram = probabl.probability_of_bigram(
                    corrected_words[i - 1], candidate
                );
            }

            if (i >= 2) {
                trigram = probabl.probability_of_trigram(
                    corrected_words[i - 2],
                    corrected_words[i - 1],
                    candidate
                );
            }

            double probability = inter.interpolate(
                unigram, bigram, trigram
            );

            if (probability > best_probability) {
                best_probability = probability;
                best_word = candidate;
            }
        }

        corrected_words.push_back(best_word);
        correct_query += best_word + " ";
    }

    return correct_query;
}



