
#include <string>
#include <vector>
#include <sstream>
#include <parser.hpp>
#include <tokens.hpp>
#include <cctype>
#include <algorithm>
#include <utility>

DocumentTokenize::DocumentTokenize(
    std::vector<std::string> doc_title_,
    std::vector<std::string> doc_content_,
    std::unordered_map<std::string, std::size_t> word_counts_

)
    : tokens_title(std::move(doc_title_)),
      tokens_content(std::move(doc_content_)), 
      word_counts(std::move(word_counts_)) {}




DocumentTokenize DocumentTokenize::tokenizeDoc(const Document &doc) {

        std::vector<std::string> tokens_title_;
        std::vector<std::string> tokens_content_;
        std::unordered_map<std::string, std::size_t> word_counts_;

        const std::string& title = doc.getTitle();
        const std::string& content = doc.getContent();

        std::string words_for_stream1;
        std::string words_for_stream2;
        std::stringstream ss1(title);
        std::stringstream ss2(content);

        while (ss1 >> words_for_stream1) {
            tokens_title_.push_back(words_for_stream1);
        }

        while (ss2 >> words_for_stream2) {
            tokens_content_.push_back(words_for_stream2);
        }

        for ( std::size_t i = 0; i <tokens_title_.size(); i++){
            word_counts_[tokens_title_[i]]++;
        } 

        for ( std::size_t i = 0; i <tokens_content_.size(); i++){
            word_counts_[tokens_content_[i]]++;
        } 

        DocumentTokenize doc_tok(
            std::move(tokens_title_),
            std::move(tokens_content_),
            std::move(word_counts_)
        );


    return doc_tok;
}


void DocumentTokenize::normalize_DocumentTokenize() {

    for (std::size_t i = 0; i < tokens_title.size(); i++) {
        std::transform(tokens_title[i].begin(),tokens_title[i].end(), tokens_title[i].begin(), [](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            }
        );
    }

    for (std::size_t i = 0; i < tokens_content.size(); i++) {
        std::transform(tokens_content[i].begin(),tokens_content[i].end(),tokens_content[i].begin(),[](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            }
        );
    }
}


void DocumentTokenize::remove_other_signs_DocumentTokenize() {
    for ( std::size_t i = 0; i < tokens_title.size(); i++){
        for ( std::size_t j = 0; j < tokens_title[i].size();){
            if(!std::isalpha(static_cast<unsigned char>(tokens_title[i][j]))){
                tokens_title[i].erase(j , 1);
            } else{
                j++;
            }
        }
    }

    for ( std::size_t i = 0; i < tokens_content.size(); i++){
        for ( std::size_t j = 0; j < tokens_content[i].size();){
            if(!std::isalpha(static_cast<unsigned char>(tokens_content[i][j]))){
                tokens_content[i].erase(j , 1);
            } else{
                j++;
            }
        }
    } 
}


//void DocumentTokenize::remove_stop_words_DocumentTokenize()

void DocumentTokenize::process() {
    normalize_DocumentTokenize();
    remove_other_signs_DocumentTokenize();
}
std::vector<DocumentTokenize> Tokenizator::tokenize(){
    std::vector<DocumentTokenize> final_tokens;
    final_tokens.reserve(docs.size());
    for ( std::size_t i = 0; i < docs.size(); i++){
        DocumentTokenize doc_for_tok = DocumentTokenize::tokenizeDoc(docs[i]);
        doc_for_tok.process();
        final_tokens.push_back(std::move(doc_for_tok));
    }
    return final_tokens;
}

