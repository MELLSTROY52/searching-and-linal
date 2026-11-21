#pragma once
#include "rapidfuzz/fuzz.hpp"
#include <memory>
#include <unordered_map> 
#include <parser.hpp>
#include <tokens.hpp>
#include <utility>


class Vocabulary{
    private:
    std::unordered_map<std::string , std::size_t> vocab;
    public:

    void build_vocabulary(const std::vector<DocumentTokenize> &docs);

    bool contains(const std::string& word) const;

    std::size_t frequency_of_word(const std::string& word) const;

    const std::unordered_map<std::string, std::size_t>& get_Vocabulary() const;

};

class SpellChecker{
    private:
    Vocabulary vocab;
    public:
    SpellChecker( Vocabulary vocab_) : vocab(std::move(vocab_)) {}

    std::vector<std::string> check(const std::vector<std::string>& query);

};

