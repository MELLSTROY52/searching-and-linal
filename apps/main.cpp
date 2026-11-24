#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <sstream>

#include <iomanip>
#include <algorithm>

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

    for (auto& doc : loaded_docs) {
    doc.set_source_file(path.filename().string());
    docs.push_back(doc);
}
}
Tokenizator tokenizator(docs);
std::vector<DocumentTokenize> tokenized_docs = tokenizator.tokenize();

Vocabulary vocabulary;
vocabulary.build_vocabulary(tokenized_docs);

NgramLanguageModel language_model(vocabulary.get_Vocabulary());
// обучение моедли каждый 5 документ откалывается для обучения лябмды остальыне используется для получения веротянтсетй
std::vector<DocumentTokenize> train_docs;
std::vector<std::string> heldout_tokens;
for (std::size_t i = 0; i < tokenized_docs.size(); i++) {
    if (i % 5 == 4) {
        for (const auto& t : tokenized_docs[i].get_tokensContent()) {
            heldout_tokens.push_back(t);
        }
    } else {
        train_docs.push_back(tokenized_docs[i]);
    }
}
language_model.train(train_docs);


Interpolation interpolation;

interpolation.train_calculation(language_model, heldout_tokens);


Document query_document("", raw_query);

DocumentTokenize tokenized_query = DocumentTokenize::tokenizeDoc(query_document);

tokenized_query.process();

std::vector<std::string> query = tokenized_query.get_tokensContent();

Advanced_choice advanced_choice(vocabulary);

auto candidates = advanced_choice.most_suitable_candidates_from_lenven(query);

std::string corrected_query =advanced_choice.the_best_choice_from_candidates(
        candidates,
        interpolation,
        language_model,
        tokenized_docs,
        query
    );

std::cout << "\n========== результаты тренировок ==========\n";

std::cout << std::fixed << std::setprecision(6);

std::cout << "Lambda unigram: "
          << interpolation.get_lambda_unigram() << '\n';

std::cout << "Lambda bigram:  "
          << interpolation.get_lambda_bigram() << '\n';

std::cout << "Lambda trigram: "
          << interpolation.get_lambda_trigram() << '\n';

std::cout << "\n============================================\n";

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
std::cout << std::fixed << std::setprecision(2);

if (corrected_query != raw_query) {
    std::cout << "corrected: " << raw_query
              << " -> " << corrected_query << "\n\n";
}

std::size_t result_number = 1;

for (const auto& doc : tokenized_docs) {

    std::size_t matched_tokens = 0;
    std::size_t total_tokens = doc.get_tokensContent().size();

    std::cout << result_number++ << ". "
              << doc.get_source_file() << " -\n\n";

    std::cout << "\"" << doc.get_original_title() << "\"\n\n";

    for (std::size_t i = 0; i < final_query.size(); i++) {

        const std::string& token = final_query[i];
        std::size_t count = 0;

        for (const auto& content_token : doc.get_tokensContent()) {
            if (content_token == token) {
                count++;
            }
        }

        matched_tokens += count;

        std::cout << token << ": " << count;

        if (i + 1 < final_query.size()) {
            std::cout << ", ";
        }
    }

    double percentage = 0.0;

    if (total_tokens > 0) {
        percentage =
            static_cast<double>(matched_tokens) /
            total_tokens * 100.0;
    }

    std::cout << "\n\ntotal: "
              << matched_tokens << " of "
              << total_tokens << " tokens ("
              << percentage << "%)\n\n";
}

return 0;
}