#include "solve.h"
#include "calc/lexer.h"
#include "calc/interpreter.h"
#include "calc/helpers.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void sync(Line &line, int index, const string &text, bool changed) {
	line.index = index;
	line.text = text;
	line.changed = changed;
}

string solve(const string &str){
	vector<Token> lexed = lex(str);
	int result = system("clear");
	for (const Token &token : lexed) {
		cout << "token: " << token.value << "\n";
	}
	return interpret(lexed);
}

void eval_lines(vector<Line*> &lines) {
	for (Line *line : lines) {
		if (line->changed) {
			line->tokens = lex(line->text);
			line->assign = has_assignment(line->tokens);
			line->changed = false;
			line -> answer = interpret(line->tokens);
			if(line->assign){
				//dependency chain cascade here
			} else {
				
			}
		}
	}
}