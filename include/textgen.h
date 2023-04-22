// Copyright 2021 GHA Test Team
#pragma once
#include <deque>
#include <string>
#include <vector>
#include <map>

typedef std::deque<std::string> prefix;
typedef std::vector<std::string> suffix;

class MarkovChains {
public:
    MarkovChains(std::map<prefix, suffix> table);
    MarkovChains(int wordsInPrefix, std::vector<std::string> words);
    MarkovChains(int wordsInPrefix, const std::string dataSetFilePath);
    std::string GenerateText(int maxWordsCount);
    std::map<prefix, suffix> GetTable();

private:
    int wordsInPrefix;
    std::map<prefix, suffix> table;

private:
    void InitTable(const std::vector<std::string> words);
    std::vector<std::string> GetWords(const std::string filePath);
    bool IsCorrectTable(const std::map<prefix, suffix> table);
};
