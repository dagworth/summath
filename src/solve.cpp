#include "solve.h"
#include "calc/lexer.h"
#include "calc/interpreter.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void sync(Line &line, int index, const string &text, bool changed) {
    line.index = index;
    line.text = text;
    line.changed = changed;
    //need to use changed in the future
}

string solve(const string &str){
	vector<Token> lexed = lex(str);
	int result = system("clear");
	for (const Token &token : lexed) {
		cout << "token: " << token.value << "\n";
	}
	return interpret(lexed);
}