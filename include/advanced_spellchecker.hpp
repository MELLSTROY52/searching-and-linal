#pragma once 
#include <utility>
#include <parser.hpp>
#include <tokens.hpp>
#include <memory>
#include <spellchecker.hpp>
#include <ngram_language_model.hpp>
#include <interpolated_language.hpp>

//std::size_t Levenshtein_func(std::string &query , std::string &word);


class Advanced_choice{
    private:
    Vocabulary vocabulary;

    public:
    Advanced_choice(const Vocabulary& vocab) : vocabulary(vocab) {}
    std::vector <std::vector<std::string>> most_suitable_candidates_from_lenven(std::vector<std::string>& query);
    std::string the_best_choice_from_candidates(std::vector<std::vector<std::string>>& candidates, Interpolation& inter , NgramLanguageModel& probabl, const std::vector<DocumentTokenize>& docs,const std::vector<std::string>& query);

};