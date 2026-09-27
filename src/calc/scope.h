#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

using namespace std;



struct Scope {
     unordered_map<string,double> variables;
     //unordered_map<string,vector<Token>> functions;
     unordered_set<string> dependencies;

     double get(const string name){
          auto a = variables.find(name);
          if (a == variables.end()) throw std::runtime_error("ts not a variable lil bro: " + name);
          return a->second;
     }
};