// Copyright 2021 GHA Test Team
#include <iostream>
#include "textgen.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    MarkovChains m = MarkovChains(2, "dataSet.txt");
    std::cout << m.GenerateText(100);
}