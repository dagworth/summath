#include "token.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Interpreter {
    const vector<Token> tokens;
    size_t index = 0;
    explicit Interpreter(const vector<Token> &tokens) : tokens(tokens) {}

    void next_expression(){
        switch(tokens[index].type){
            case TokenType::If:
            case TokenType::Def:
            case TokenType::For:
            case TokenType::Identifier:
            case TokenType::Number:
            case TokenType::Neg:
        }
        index++;
    };
};

string interpret(const std::vector<Token> &tokens) {
     Interpreter interpreter(tokens);
     while(interpreter.index != interpreter.tokens.size()){
        interpreter.next_expression();
     }
     return "ur mom";
}