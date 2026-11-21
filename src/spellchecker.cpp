#include <rapidfuzz/distance/Levenshtein.hpp>
#include <memory>
#include <unordered_map> 
#include <parser.hpp>
#include <tokens.hpp>
#include <utility>
#include <spellchecker.hpp>

void Vocabulary::build_vocabulary(const std::vector<DocumentTokenize> &docs){
    for ( std::size_t i = 0; i < docs.size(); i++){
        for ( std::size_t j = 0; j < docs[i].get_tokensContent().size(); j++){
            vocab[docs[i].get_tokensContent()[j]]++;
        }
    }
    for ( std::size_t i = 0; i < docs.size(); i++){
        for ( std::size_t j = 0; j < docs[i].get_tokensTitle().size(); j++){
            vocab[docs[i].get_tokensTitle()[j]]++;
        }
    }

}
bool Vocabulary::contains(const std::string& word) const {
    if  (vocab.find(word) != vocab.end()){
        return true;
    }else{
        return false;
    }
}


std::size_t Vocabulary::frequency_of_word(const std::string& word) const{
    if (contains(word) == true){
        return vocab.at(word);
    }else{
        return 0;
    }
}

const std::unordered_map<std::string, std::size_t>& Vocabulary::get_Vocabulary() const {
    return vocab;
}


std::vector<std::string> SpellChecker::check(const std::vector<std::string>& query) {
    std::vector<std::string> corrected_query = query;

    const auto& vocabulary = vocab.get_Vocabulary();

    for (std::size_t i = 0; i < corrected_query.size(); i++) {

        if (vocab.contains(corrected_query[i])) {
            continue;
        }

        std::size_t old_distance = 3;
        std::string suitable_word = corrected_query[i];
        std::size_t max_frequency = 0;

        for (const auto& [key, value] : vocabulary) {

            std::size_t distance = rapidfuzz::levenshtein::distance(key, corrected_query[i]);

            if (distance > 2) {
                continue;
            }

            if (distance < old_distance) {
                old_distance = distance;
                suitable_word = key;
                max_frequency = value;
            }
            else if (distance == old_distance && value > max_frequency) {
                suitable_word = key;
                max_frequency = value;
            }
        }

        corrected_query[i] = suitable_word;
    }

    return corrected_query;
}

