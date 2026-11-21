#pragma once 
#include <utility>
#include <parser.hpp>
#include <tokens.hpp>
#include <memory>

std::size_t Levenshtein_func(std::string &query , std::string &word);