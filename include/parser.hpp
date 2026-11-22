#pragma once
#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <unordered_map>
#include <rapidcsv.h>


using json = nlohmann::json;
namespace fs = std::filesystem;

class Document {
private:
    std::string title;
    std::string content;
    std::string source_file;

public:
    void set_source_file(const std::string& file) {
    source_file = file;
}

const std::string& get_source_file() const {
    return source_file;
}
    Document(std::string title_, std::string content_)
        : title(std::move(title_)), content(std::move(content_)) {}

    const std::string& getTitle() const {
        return title;
    }

    const std::string& getContent() const {
        return content;
    }
};


class DocumentReader {
public:
    virtual ~DocumentReader() = default;

    virtual std::vector<Document> read( const std::filesystem::path& path) const = 0;
};


class Reader_for_Json : public DocumentReader {
public:
    std::vector<Document> read(const std::filesystem::path& path) const override;
};


class Reader_for_CSV : public DocumentReader {
public:
    std::vector<Document> read( const std::filesystem::path& path) const override;
};


class Reader_for_XL : public DocumentReader {
public:
    std::vector<Document> read(const std::filesystem::path& path) const override;
};
