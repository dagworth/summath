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

struct Lexer {
    const string &str;
    size_t index = -1;
    char cur = '\0';
    char peek = '\0';

    explicit Lexer(const string &str) : str(str) {}

    char next() {
        index++;
        cur = index < str.length() ? str[index] : '\0';
        peek = index + 1 < str.length() ? str[index + 1] : '\0';
        return cur;
    }
};

bool is_digit(char c){
    return c >= '0' && c <= '9' || c == '.';
}

vector<Token> lex(const string &str) {
    vector<Token> tokens;
    Lexer lexer(str);

    while (lexer.next() != '\0') {

        // if(is_digit(lexer.cur)){
        //     int start =
        //     while(is_digit(lexer.peek)){
        //         lexer.next();
        //     }

        // }


        if(lexer.cur == '+'){
            if(lexer.peek == '+'){
                tokens.emplace_back(TokenType::AssignAddOne,  "++");
                lexer.next();
            } else if (lexer.peek == '=') {
                tokens.emplace_back(TokenType::AssignAdd,  "+=");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Add,  "+");
            }
            continue;
        }

        if(lexer.cur == '-'){
            if(lexer.peek == '-'){
                tokens.emplace_back(TokenType::AssignSubOne,  "--");
                lexer.next();
            } else if (lexer.peek == '=') {
                tokens.emplace_back(TokenType::AssignSub,  "-=");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Neg,  "-");
            }
            continue;
        }

        if(lexer.cur == '/'){
            if (lexer.peek == '=') {
                tokens.emplace_back(TokenType::AssignDiv,  "/=");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Div,  "/");
            }
            continue;
        }

        if(lexer.cur == '*'){
            if (lexer.peek == '=') {
                tokens.emplace_back(TokenType::AssignMul,  "*=");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Mul,  "*");
            }
            continue;
        }
    }

    return tokens;
}