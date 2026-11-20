#include "rapidfuzz/fuzz.hpp"
#include <memory>
#include <unordered_map> 
#include <parser.hpp>
#include <tokens.hpp>
#include <utility>
#include <spellchecker.hpp>

void Vocabulary::build_vocabulary(const std::vector<DocumentTokenize> &docs){
    for ( std::size_t i = 0; i < docs.size(); i++){
        for ( std::size_t j = 0; j < docs[i].size(); j++){
            vocab.insert(docs[i].get_tokensContent([j]))
        }
    }
}


