#include "lexer.h"
#include "token.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const unordered_map<string, TokenType> keywords = {
    {"sin", TokenType::Sin},
    {"cos", TokenType::Cos},
    {"pi",  TokenType::Pi},
    {"if",  TokenType::If},
    {"for",  TokenType::For},
    {"end",  TokenType::End},
    {"degtorad",  TokenType::DegToRad},
    {"radtodeg",  TokenType::RadToDeg},
};

vector<Token> lex(const string &line) {
    vector<Token> tokens;

    for(int i = 0; i < line.length(); i++){
        char c = line[i];
    }

    return tokens;
}