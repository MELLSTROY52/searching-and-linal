#include "parser.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <rapidcsv.h>
#include <OpenXLSX.hpp>
#include <utility>

using json = nlohmann::json;
namespace fs = std::filesystem;


std::vector<Document> Reader_for_Json::read(const std::filesystem::path& path) const {

    std::vector<Document> docs;

    if (!fs::exists(path)) {
        throw std::runtime_error("не сущестувет файла: " + path.string());
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("не получлось отркыть файл  " + path.string());
    }

    json j;
    file >> j;

    if (!j.is_array()) {
        throw std::runtime_error("файл олжен иметь данные отправте корректные данныу");
    }
    docs.reserve(j.size());

    for (const auto& e : j) {
        Document doc(
            e.at("title").get<std::string>(),
            e.at("content").get<std::string>()
        );
        docs.push_back(doc);
    }

    return docs;
}

std::vector<Document> Reader_for_CSV::read(const std::filesystem::path& path) const {

    std::vector<Document> docs;

    if (!fs::exists(path)) {
        throw std::runtime_error("не существует файла  " + path.string());
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("не полулчось открыть файл  " + path.string());
    }

    rapidcsv::Document csv(file);

    std::vector<std::string> titles = csv.GetColumn<std::string>("title");

    std::vector<std::string> contents = csv.GetColumn<std::string>("content");

    if (titles.size() != contents.size()) {
        throw std::runtime_error("отправьте норм таблицу");
    }

    docs.reserve(titles.size());

    for (std::size_t i = 0; i < titles.size(); i++) {
        Document doc(
            std::move(titles[i]),
            std::move(contents[i])
        );
        docs.push_back(doc);
    }

    return docs;
}

std::vector<Document> Reader_for_XL::read(const std::filesystem::path& path) const {

    if (!fs::exists(path)) {
        throw std::runtime_error("не сущестует фаайла  " + path.string());
    }

    std::vector<Document> docs;

    OpenXLSX::XLDocument file;

    file.open(path.string());

    OpenXLSX::XLWorkbook workbook = file.workbook();
    OpenXLSX::XLWorksheet sheet = workbook.worksheet("Sheet1");


    for (auto row = 2u; row <= sheet.rowCount(); row++) {
        Document doc(
            sheet.cell(row, 1).getString(),
            sheet.cell(row, 2).getString()
        );
        docs.push_back(doc);
    }

    file.close();

    return docs;
}

