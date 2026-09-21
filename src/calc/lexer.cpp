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
    {"do",  TokenType::Do},
    {"true", TokenType::True},
    {"false", TokenType::False},
    {"end",  TokenType::End},
    {"def", TokenType::Def},
    {"degtorad",  TokenType::DegToRad},
    {"radtodeg",  TokenType::RadToDeg},
};

struct Lexer {
    const string &str;
    unordered_set<string> ids = {};
    size_t index = -1;
    char cur = '\0';
    char peek = '\0';

    explicit Lexer(const string &str) : str(str) {}

    char next(bool skip = true) {
        index++;
        cur = index < str.length() ? str[index] : '\0';
        peek = index+1 < str.length() ? str[index+1] : '\0';
        return cur;
    }

    string check_if_id(const string &word){
        for(int i = 0; i < word.length(); i++){
            string sub = word.substr(0,i+1);
            if(ids.find(sub) != ids.end()){
                return sub;
            }
        }
        return "";
    }
};

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

vector<Token> lex(const string &str) {
    vector<Token> tokens;
    Lexer lexer(str);

    while (lexer.next() != '\0') {
        if(lexer.cur == ' ' || lexer.cur == '\t'){
            continue;
        }

        if(lexer.cur == '\n'){
            tokens.emplace_back(TokenType::EndLine, "endline");
            continue;
        }

        if(is_number(lexer.cur)){
            int start = lexer.index;
            while(is_number(lexer.peek)){
                lexer.next();
            }
            tokens.emplace_back(TokenType::Number,  lexer.str.substr(start, lexer.index - start + 1));
            continue;
        }

        if(is_alpha(lexer.cur)){
            int start = lexer.index;
            while(is_alpha(lexer.peek) || is_digit(lexer.peek)){
                lexer.next(false);
            }
            string word = lexer.str.substr(start, lexer.index - start + 1);

            if(keywords.count(word)){
                tokens.emplace_back(keywords.at(word),  word);
            } else {
                string potential_id = lexer.check_if_id(word);
                while(potential_id != ""){
                    tokens.emplace_back(TokenType::Identifier,  "potential id " + potential_id);
                    word = word.substr(potential_id.length(),word.length()-potential_id.length());
                    potential_id = lexer.check_if_id(word);
                }
                if(word != ""){
                    if(lexer.peek == '=' && !lexer.ids.contains(word)){
                        lexer.ids.insert(word);
                    }
                    tokens.emplace_back(TokenType::Identifier,  word);
                }
            }
            continue;
        }

        if(lexer.cur == '('){
            tokens.emplace_back(TokenType::LParen,  "(");
            continue;
        }

        if(lexer.cur == ')'){
            tokens.emplace_back(TokenType::RParen,  ")");
            continue;
        }

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

        if(lexer.cur == '%'){
            if (lexer.peek == '=') {
                tokens.emplace_back(TokenType::AssignMod,  "%=");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Mod,  "%");
            }
            continue;
        }

        if(lexer.cur == '^'){
            if (lexer.peek == '=') {
                tokens.emplace_back(TokenType::AssignPow,  "^=");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Pow,  "^");
            }
            continue;
        }

        if(lexer.cur == '='){
            if (lexer.peek == '=') {
                tokens.emplace_back(TokenType::Equals,  "==");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Assign,  "=");
            }
            continue;
        }

        if(lexer.cur == '&' && lexer.peek == '&'){
            tokens.emplace_back(TokenType::CompareAnd,  "&&");
            lexer.next();
            continue;
        }

        if(lexer.cur == '|' && lexer.peek == '|'){
            tokens.emplace_back(TokenType::CompareOr,  "||");
            lexer.next();
            continue;
        }

        if(lexer.cur == ','){
            tokens.emplace_back(TokenType::Comma,  ",");
            continue;
        }

        if(lexer.cur == '!'){
            if(lexer.peek == '='){
                tokens.emplace_back(TokenType::CompareNAnd,  "!=");
                lexer.next();
            } else {
                tokens.emplace_back(TokenType::Not,  "!");
            }
            continue;
        }
    }

    return tokens;
}