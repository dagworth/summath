#include "token.h"
#include "scope.h"
#include "helpers.h"

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <unordered_map>

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

using BinOp = double (*)(double, double);

static const unordered_map<TokenType, BinOp> ops = {
    {TokenType::Add, [](double a, double b) { return a+b; }},
    {TokenType::Neg, [](double a, double b) { return a-b; }},
    {TokenType::Mul, [](double a, double b) { return a*b; }},
    {TokenType::Div, [](double a, double b) { return a/b; }},
    {TokenType::Mod, [](double a, double b) { return fmod(a,b); }},
    {TokenType::Pow, [](double a, double b) { return pow(a,b); }},
};

static const unordered_map<TokenType, BinOp> assignments = {
    {TokenType::Add, [](double a, double b) { return a+b; }},
    {TokenType::Neg, [](double a, double b) { return a-b; }},
    {TokenType::Mul, [](double a, double b) { return a*b; }},
    {TokenType::Div, [](double a, double b) { return a/b; }},
    {TokenType::Mod, [](double a, double b) { return fmod(a,b); }},
    {TokenType::Pow, [](double a, double b) { return pow(a,b); }},
};

struct Interpreter {
    const vector<Token> &tokens;
    Scope &local_scope;
    Scope &scope;
    size_t index = 0;

    Interpreter(const vector<Token> &tokens, Scope &local_scope, Scope &scope) : tokens(tokens), scope(scope), local_scope(local_scope) {}

    TokenType get_token_type(int i){
        if(i < tokens.size()){
            return tokens[i].type;
        }
        return TokenType::None;
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
            double result = eval();
            if(token.type == TokenType::RParen){
                index++;
            }
            return result;
        }

        //we need right parentheses to work
        throw runtime_error("not a number or valid var");
    }

    double eval(){
        if(get_token_type(index) == TokenType::Identifier && is_assignment(get_token_type(index+1))){
            index+=2;
            double value = eval();
            scope.variables[tokens[index].value] = value;
            return value;
        }

        double result = eval_num();
        while(index < tokens.size()){
            auto op = ops.find(tokens[index].type);
            if (op == ops.end()) break;
            index++;
            result = op->second(result, eval_num());
        }

        return result;
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