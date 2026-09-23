#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "calc/token.h"
#include "calc/scope.h"

using namespace std;

struct Line {
     int index = -1;
     string text;
     vector<Token> tokens;
     bool changed = true;
     bool assign = true;
     string answer;
     Scope scope;
     int looped = 1;
};

void sync(Line &line, int index, const string &text, bool changed);

string solve(const string &input);

void eval_lines(vector<Line*> &lines);