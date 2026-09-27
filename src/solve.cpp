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

void test_lex(const string &str){
	vector<Token> lexed = lex(str);
	int result = system("clear");
	for (const Token &token : lexed) {
		cout << "token: " << token.value << "\n";
	};
}

//make the scope here, for every line that changed

Scope make_full_scope(vector<Line*> &lines, int index){
	Scope new_scope; //for now
	return new_scope;
}

void eval_lines(vector<Line*> &lines) {
	for (Line *line : lines) {
		if (line->changed) {
			line->tokens = lex(line->text);
			line->assign = has_assignment(line->tokens);
			line->changed = false;
			Scope a = make_full_scope(lines, line->index);
			Scope local_scope;
			line -> answer = interpret(line->tokens, local_scope, a);
			if(line->assign){
				//dependency chain cascade here
			} else {
				
			}
		}
	}
}