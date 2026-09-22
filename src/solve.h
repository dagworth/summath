#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "calc/token.h"

struct Scope {
     std::unordered_map<std::string,double> variables;
     std::unordered_set<std::string> dependencies;
};

struct Line {
     int index = -1;
     std::string text;
     std::vector<Token> tokens;
     bool changed = true;
     bool assign = true;
     std::string answer;
     Scope scope;
};

void sync(Line &line, int index, const std::string &text, bool changed);

std::string solve(const std::string &input);

void eval_lines(std::vector<Line*> &lines);