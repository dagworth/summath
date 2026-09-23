#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Scope {
     unordered_map<string,double> variables;
     unordered_set<string> dependencies;
};
