#include "token.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Interpreter {
    const vector<Token> tokens;
    unordered_map<string,double> ids = {};
//     unordered_map<string,Function> functions = {};
    size_t index = -1;

    explicit Interpreter(const vector<Token> &tokens) : tokens(tokens) {}
};

string interpret(const std::vector<Token> &tokens) {
     Interpreter interpreter(tokens);

     return "ur mom";
}