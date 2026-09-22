#include "lexer.h"
#include "helpers.h"
#include "token.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Lexer {
    vector<Token> tokens;
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

    void tokenize(){
        if(cur == ' ' || cur == '\t'){
            return;
        }

        if(cur == '\n'){
            tokens.emplace_back(TokenType::EndLine, "endline");
            return;
        }

        if(is_number(cur)){
            int start = index;
            while(is_number(peek)){
                next();
            }
            tokens.emplace_back(TokenType::Number,  str.substr(start, index - start + 1));
            return;
        }

        if(is_alpha(cur)){
            int start = index;
            while(is_alpha(peek) || is_digit(peek)){
                next(false);
            }
            string word = str.substr(start, index - start + 1);

            if(is_keyword(word)){
                tokens.emplace_back(keyword_to_token(word),  word);
                return;
            } else {
                string potential_id = check_if_id(word);
                while(potential_id != ""){
                    tokens.emplace_back(TokenType::Identifier,  potential_id);
                    word = word.substr(potential_id.length(),word.length()-potential_id.length());
                    potential_id = check_if_id(word);
                }
                if(word != ""){
                    if(peek == '=' && !ids.contains(word)){
                        ids.insert(word);
                    }
                    tokens.emplace_back(TokenType::Identifier,  word);
                }
            }
            return;
        }

        if(cur == '('){
            tokens.emplace_back(TokenType::LParen,  "(");
            return;
        }

        if(cur == ')'){
            tokens.emplace_back(TokenType::RParen,  ")");
            return;
        }

        if(cur == '+'){
            if(peek == '+'){
                tokens.emplace_back(TokenType::AssignAddOne,  "++");
                next();
            } else if (peek == '=') {
                tokens.emplace_back(TokenType::AssignAdd,  "+=");
                next();
            } else {
                tokens.emplace_back(TokenType::Add,  "+");
            }
            return;
        }

        if(cur == '-'){
            if(peek == '-'){
                tokens.emplace_back(TokenType::AssignSubOne,  "--");
                next();
            } else if (peek == '=') {
                tokens.emplace_back(TokenType::AssignSub,  "-=");
                next();
            } else {
                tokens.emplace_back(TokenType::Neg,  "-");
            }
            return;
        }

        if(cur == '/'){
            if (peek == '=') {
                tokens.emplace_back(TokenType::AssignDiv,  "/=");
                next();
            } else {
                tokens.emplace_back(TokenType::Div,  "/");
            }
            return;
        }

        if(cur == '*'){
            if (peek == '=') {
                tokens.emplace_back(TokenType::AssignMul,  "*=");
                next();
            } else {
                tokens.emplace_back(TokenType::Mul,  "*");
            }
            return;
        }

        if(cur == '%'){
            if (peek == '=') {
                tokens.emplace_back(TokenType::AssignMod,  "%=");
                next();
            } else {
                tokens.emplace_back(TokenType::Mod,  "%");
            }
            return;
        }

        if(cur == '^'){
            if (peek == '=') {
                tokens.emplace_back(TokenType::AssignPow,  "^=");
                next();
            } else {
                tokens.emplace_back(TokenType::Pow,  "^");
            }
            return;
        }

        if(cur == '='){
            if (peek == '=') {
                tokens.emplace_back(TokenType::Equals,  "==");
                next();
            } else {
                tokens.emplace_back(TokenType::Assign,  "=");
            }
            return;
        }

        if(cur == '>'){
            if (peek == '=') {
                tokens.emplace_back(TokenType::GreaterEq,  ">=");
                next();
            } else {
                tokens.emplace_back(TokenType::Greater,  ">");
            }
            return;
        }

        if(cur == '<'){
            if (peek == '=') {
                tokens.emplace_back(TokenType::LessEq,  "<=");
                next();
            } else {
                tokens.emplace_back(TokenType::Less,  "<");
            }
            return;
        }

        if(cur == '&' && peek == '&'){
            tokens.emplace_back(TokenType::CompareAnd,  "&&");
            next();
            return;
        }

        if(cur == '|' && peek == '|'){
            tokens.emplace_back(TokenType::CompareOr,  "||");
            next();
            return;
        }

        if(cur == ','){
            tokens.emplace_back(TokenType::Comma,  ",");
            return;
        }

        if(cur == '!'){
            if(peek == '='){
                tokens.emplace_back(TokenType::CompareNAnd,  "!=");
                next();
            } else {
                tokens.emplace_back(TokenType::Not,  "!");
            }
            return;
        }
    }
};

vector<Token> lex(const string &str) {
    Lexer lexer(str);
    while (lexer.next() != '\0') {
        lexer.tokenize();
    }
    return lexer.tokens;
}