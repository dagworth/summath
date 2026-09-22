#include "token.h"
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

bool is_digit(char c){
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

bool is_number(char c){
    return is_digit(c) || c == '.';
}

bool is_alpha(char c){
    switch (c) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return true;
        default:
            return false;
    }
}

const unordered_map<string, TokenType> keywords = {
    {"sin", TokenType::Sin},
    {"cos", TokenType::Cos},
    {"pi",  TokenType::Pi},
    {"if",  TokenType::If},
    {"for",  TokenType::For},
    {"do",  TokenType::Do},
    {"true", TokenType::True},
    {"false", TokenType::False},
    {"end",  TokenType::End},
    {"def", TokenType::Def},
    {"degtorad",  TokenType::DegToRad},
    {"radtodeg",  TokenType::RadToDeg},
};

bool is_keyword(string str){
     return keywords.count(str);
}

TokenType keyword_to_token(string str){
     return keywords.at(str);
}

bool has_assignment(vector<Token> tokens){
     for (const Token& t : tokens) {
          switch(t.type) {
               case TokenType::Assign:
               case TokenType::AssignAdd:
               case TokenType::AssignAddOne:
               case TokenType::AssignDiv:
               case TokenType::AssignMod:
               case TokenType::AssignMul:
               case TokenType::AssignPow:
               case TokenType::AssignSub:
               case TokenType::AssignSubOne:
                    return true;
          }
     };
     return false;
};