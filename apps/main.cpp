#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <sstream>

#include "parser.hpp"
#include "tokens.hpp"
#include "spellchecker.hpp"
#include "advanced_spellchecker.hpp"
#include "ngram_language_model.hpp"
#include "interpolated_language.hpp"
#include "relevance.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Недостатнчо переданных параметров";
        return 1;
    }

    std::size_t top_k = 0;
    std::vector<std::string> files;
    std::string raw_query;

for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--docs") {
        if (++i >= argc) return 1;
        files.push_back(argv[i]);
    }
    else if (arg == "--query") {
        if (++i >= argc) return 1;
        raw_query = argv[i];
    }
    else if (arg == "--top") {
        if (++i >= argc) return 1;

        try {
            top_k = std::stoi(argv[i]);
            if (top_k == 0) return 1;
        }
        catch (...) {
            return 1;
        }
    }
    else {
        std::cerr << "Неизвестный параметр: " << arg << '\n';
        return 1;
    }
}
    if (files.empty() || raw_query.empty()) {
    std::cerr << "Укажите документы и поисковый запрос";
    return 1;
}

std::vector<Document> docs;


    for (const auto& file : files) {
    fs::path path(file);
    std::string ext = path.extension().string();

    std::unique_ptr<DocumentReader> reader;

    if (ext == ".json")
        reader = std::make_unique<Reader_for_Json>();
    else if (ext == ".csv")
        reader = std::make_unique<Reader_for_CSV>();
    else if (ext == ".xlsx" || ext == ".xls")
        reader = std::make_unique<Reader_for_XL>();
    else {
        std::cerr << "Неподдерживаемый формат: " << file << '\n';
        return 1;
    }

    std::vector<Document> loaded_docs = reader->read(path);

    for (const auto& doc : loaded_docs)
        docs.push_back(doc);
}
Tokenizator tokenizator(docs);
std::vector<DocumentTokenize> tokenized_docs = tokenizator.tokenize();

Vocabulary vocabulary;
vocabulary.build_vocabulary(tokenized_docs);

NgramLanguageModel language_model(vocabulary.get_Vocabulary());

language_model.train(tokenized_docs);

Document query_document("", raw_query);

DocumentTokenize tokenized_query = DocumentTokenize::tokenizeDoc(query_document);

tokenized_query.process();

std::vector<std::string> query = tokenized_query.get_tokensContent();

Interpolation interpolation;

Advanced_choice advanced_choice(vocabulary);

auto candidates = advanced_choice.most_suitable_candidates_from_lenven(query);

std::string corrected_query =advanced_choice.the_best_choice_from_candidates(
        candidates,
        interpolation,
        language_model,
        tokenized_docs,
        query
    );

std::vector<std::string> final_query;

std::istringstream stream(corrected_query);
std::string word;

while (stream >> word) {
    final_query.push_back(word);
}

Relevance_Counter::most_suit_docs(tokenized_docs, final_query);
Relevance_Counter::remove_zero_docs(tokenized_docs, final_query);

if (top_k != 0 && tokenized_docs.size() > top_k) {
    tokenized_docs.erase(
        tokenized_docs.begin() + top_k,
        tokenized_docs.end()
    );
}
for (const auto& doc : tokenized_docs) {
    for (const auto& token : doc.get_tokensTitle()) {
        std::cout << token << " ";
    }
    std::cout << '\n';
}
}
