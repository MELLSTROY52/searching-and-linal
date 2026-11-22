#pragma once
#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <unordered_map>
#include <rapidcsv.h>
#include <sstream>

#include <algorithm>

#include <parser.hpp>

class DocumentTokenize {
private:
    std::vector<std::string> tokens_title;
    std::vector<std::string> tokens_content;
    std::unordered_map<std::string, std::size_t> word_counts;

    void normalize_DocumentTokenize();
    void remove_other_signs_DocumentTokenize();
    void remove_stop_words_DocumentTokenize();

public:

    DocumentTokenize(
        std::vector<std::string> doc_title_,
        std::vector<std::string> doc_content_,
        std::unordered_map<std::string, std::size_t> word_counts
    );
    static DocumentTokenize tokenizeDoc(const Document &doc);

    void process();

    const std::vector<std::string>& get_tokensTitle() const  { return tokens_title;}
    const std::vector<std::string>& get_tokensContent() const  {return tokens_content;}
    const std::unordered_map<std::string, std::size_t>& get_word_counts() const {return word_counts;}


};

class Tokenizator {
    private:
    std::vector<Document> docs;
    public:
    Tokenizator( std::vector<Document> data_for_tokens) : docs(std::move(data_for_tokens)) {}

    std::vector<DocumentTokenize> tokenize();
    
};
