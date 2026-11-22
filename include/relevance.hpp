#pragma once

#include <tokens.hpp>
#include <parser.hpp>
#include <unordered_map>
#include <memory>

class Relevance_Counter{
    public:
    static void most_suit_docs( std::vector<DocumentTokenize>& all_docs , const std::vector<std::string>& query);
    static void remove_zero_docs(std::vector<DocumentTokenize>& all_docs , const  std::vector<std::string>& query);
};