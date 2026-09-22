#pragma once

#include <string>
#include <vector>
#include "calc/token.h"

struct Line {
    int index = -1;
    std::string text;
    std::vector<Token> tokens;
    bool changed = true;
};

void sync(Line &line, int index, const std::string &text, bool changed);

std::string solve(const std::string &input);