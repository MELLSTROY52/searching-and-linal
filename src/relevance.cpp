#include <tokens.hpp>
#include <parser.hpp>
#include <unordered_map>
#include <memory>
#include <relevance.hpp>
#include <algorithm>


void Relevance_Counter::most_suit_docs( std::vector<DocumentTokenize>& all_docs, 
const std::vector<std::string>& query){
    std::size_t n = query.size();
    std::stable_sort(all_docs.begin() , all_docs.end() ,[&n , &query]
    (const DocumentTokenize& a ,  const DocumentTokenize& b){
        std::size_t match_in_a = 0;
        std::size_t match_in_b = 0;
        for ( std::size_t i = 0; i < n; i++){
            if ( a.get_word_counts().find(query[i]) != a.get_word_counts().end()){
                match_in_a += a.get_word_counts().at(query[i]);
            }
        }
        for ( std::size_t i = 0; i < n; i++){
            if ( b.get_word_counts().find(query[i]) != b.get_word_counts().end()){
                match_in_b += b.get_word_counts().at(query[i]);
            }
        }
        return match_in_a > match_in_b;
    });
}
void Relevance_Counter::remove_zero_docs(std::vector<DocumentTokenize>& all_docs, const std::vector<std::string>& query) {
    for (auto i = all_docs.begin(); i != all_docs.end();) {
        std::size_t relevance = 0;

        for (const auto& token : query) {
            auto found = i->get_word_counts().find(token);
            if (found != i->get_word_counts().end()) {
                relevance += found->second;
            }
        }

        if (relevance == 0) {
            i = all_docs.erase(i);
        } else {
            ++i;
        }
    }
}