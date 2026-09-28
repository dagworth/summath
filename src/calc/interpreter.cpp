#include "token.h"
#include "scope.h"
#include "helpers.h"

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>
#include <functional>

using namespace std;

string format_number(double value) {
    if (value == (long long)value) {
        return to_string((long long)value);
    }
    string str = to_string(value);
    while (str.back() == '0') str.pop_back();
    if (str.back() == '.') str.pop_back();
    return str;
}

struct Interpreter {
    vector<Token> tokens;
    Scope &local_scope;
    Scope &scope;
    size_t index = 0;

    Interpreter(const vector<Token> &tokens, Scope &local_scope, Scope &scope) : tokens(tokens), scope(scope), local_scope(local_scope) {}

    TokenType get_token_type(size_t i){
        if(i < tokens.size()){
            return tokens[i].type;
        }
        return TokenType::None;
    }

    //R_parens dont need to be balanced because they dont really matter
    void balance_L_parens(){
        int count = 0;
        for (size_t i = index; i < tokens.size(); i++) {
            if (tokens[i].type == TokenType::LParen) count--;
            else if (tokens[i].type == TokenType::RParen) count++;
        }
        if (count > 0)  tokens.insert(tokens.begin() + index, count, Token{TokenType::LParen, "("});
    }

    double eval_num() {
        if(index >= tokens.size()){
            throw runtime_error("ur mother is fat");
        }
        Token token = tokens[index];
        if (token.type == TokenType::Number) {
            index++;
            return stod(token.value);
        }
        if (token.type == TokenType::Identifier) {
            index++;
            local_scope.dependencies.insert(token.value);
            return scope.get(token.value);
        }
        if(token.type == TokenType::LParen){
            index++;
            double result = eval(true);
            if(get_token_type(index) == TokenType::RParen){
                index++;
            }
            return result;
        }

        throw runtime_error("not a number or valid var");
    }

    double eval_level(const function<double()> &next, const unordered_map<TokenType, function<double(double,double)>> &ops){
        double result = next();
        while(index < tokens.size()){
            auto op = ops.find(get_token_type(index));
            if(op == ops.end()) break;
            index++;
            result = op->second(result, next());
        }
        return result;
    }

    double eval_pow_mod(){
        static const unordered_map<TokenType, function<double(double,double)>> ops = {
            {TokenType::Mod, [](double a, double b){ return fmod(a,b); }},
            {TokenType::Pow, [](double a, double b){ return pow(a,b); }},
        };
        return eval_level([this]{ return eval_num(); }, ops);
    }

    double eval_muldiv(){
        static const unordered_map<TokenType, function<double(double,double)>> ops = {
            {TokenType::Mul, [](double a, double b){ return a*b; }},
            {TokenType::Div, [](double a, double b){ return a/b; }},
        };
        return eval_level([this]{ return eval_pow_mod(); }, ops);
    }

    double eval_binops(){
        static const unordered_map<TokenType, function<double(double,double)>> ops = {
            {TokenType::Add, [](double a, double b){ return a+b; }},
            {TokenType::Neg, [](double a, double b){ return a-b; }},
        };
        return eval_level([this]{ return eval_muldiv(); }, ops);
    }

    double eval(bool in_parens = false){
        if(get_token_type(index) == TokenType::Identifier && is_assignment(get_token_type(index+1))){
            string n = tokens[index].value;
            index += 2;
            scope.variables[n] = eval(in_parens);
            return scope.variables[n];
        }

        if(!in_parens) balance_L_parens(); //this kinda runs like a lot of times but whatever, its o(n)
        return eval_binops();
    }
};

string interpret(const vector<Token> &tokens, Scope &local_scope, Scope &scope) {
    if (tokens.empty()) {
        return "empty"; //shouldnt really happen cus lines always have endline
    }
    try {
        Interpreter interpreter(tokens,local_scope, scope);
        return format_number(interpreter.eval());
    } catch (const exception &e) {
        return e.what();
    }
}