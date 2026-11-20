#pragma once

#include <tokens.hpp>
#include <parser.hpp>
#include <unordered_map>
#include <memory>

class Relevance_Counter{
    private:
    std::unordered_map< std::string, std::size_t > count_words;
    public:
    

};