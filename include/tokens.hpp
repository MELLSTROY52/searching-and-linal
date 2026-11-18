#pragma once
#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <unordered_map>
#include <rapidcsv.h>
#include <sstream>

#include <parser.hpp>

class Tokenizator {
    private:
    std::vector<Document> docs;

    std::vector<std::string> tokenize();
    std::vector<std::string> normalize();
    std::vector<std::string> remove_small_words();
    public:
    Tokenizator( std::vector<Document> data_for_tokens) : docs(std::move(data_for_tokens)) {}
    std::vector<std::string> steps();
};
