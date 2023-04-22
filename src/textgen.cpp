// Copyright 2021 GHA Test Team
#include "textgen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

MarkovChains::MarkovChains(std::map<prefix, suffix> table) {
    if (IsCorrectTable(table)) {
        wordsInPrefix = table.begin()->first.size();
        this->table = table;
    } else {
        throw std::invalid_argument("Incorrect table");
    }
}

bool MarkovChains::IsCorrectTable(const std::map<prefix, suffix> table) {
    if (table.empty())
        return true;

    int wordsInPrefix = table.begin()->first.size();
    for (auto element : table) {
        if (element.first.size() != wordsInPrefix)
            return false;
    }
    return true;
}

MarkovChains::MarkovChains(int prefixSize, std::vector<std::string> words) {
    this->wordsInPrefix = prefixSize;
    InitTable(words);
}

MarkovChains::MarkovChains(int prefixSize, std::string dataSetFilePath) {
    this->wordsInPrefix = prefixSize;
    InitTable(GetWords(dataSetFilePath));
}

std::string MarkovChains::GenerateText(int maxWordsCount) {
    if (maxWordsCount < 0)
        throw std::invalid_argument("maxLength must be >= 0");

    if (maxWordsCount < wordsInPrefix)
        throw std::invalid_argument("maxLength must be >= than prefix size");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, table.size() - 1);

    prefix currentPrefix = table.begin()->first;

    std::string text;
    for (int i = 0; i < currentPrefix.size(); i++)
        text += currentPrefix[i] + " ";

    for (int i = 0; i < maxWordsCount - wordsInPrefix; i++) {
        suffix currentSuffix;

        auto it = table.find(currentPrefix);
        if (it != table.end())
            currentSuffix = it->second;

        if (currentSuffix.size() == 0)
            break;

        int index = dist(gen) % currentSuffix.size();
        text += currentSuffix[index] + " ";

        currentPrefix.pop_front();
        currentPrefix.push_back(currentSuffix[index]);
    }

    if (!text.empty())
        text.erase(text.size() - 1);

    return text;
}

std::map<prefix, suffix> MarkovChains::GetTable() {
    return table;
}

void MarkovChains::InitTable(const std::vector<std::string> words) {
    prefix currentPrefix;

    for (std::string word : words) {
        if (currentPrefix.size() == wordsInPrefix) {
            table[currentPrefix].push_back(word);
            currentPrefix.pop_front();
        }
        currentPrefix.push_back(word);
    }
}

std::vector<std::string> MarkovChains::GetWords(const std::string filePath) {
    std::ifstream dataFile(filePath);
    if (!dataFile.is_open()) {
        std::cerr << "Error : Cannot open file " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> words;
    std::string line;

    while (std::getline(dataFile, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word)
            words.push_back(word);
    }
    dataFile.close();
    return words;
}
