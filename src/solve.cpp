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

Scope make_full_scope(vector<Line*> &lines, int index){
	Scope new_scope;
	for(int i = index; i >= 0; i--){
		for(const auto &entry : lines[i]->scope.variables){
			if(new_scope.variables.find(entry.first) == new_scope.variables.end()){
				new_scope.variables[entry.first] = entry.second;
			}
		}
	}
	return new_scope;
}

void eval_lines(vector<Line*> &lines) {
	int result = system("clear");
	for (Line *line : lines) {
		if (line->changed) {
			line->tokens = lex(line->text);
			line->assign = has_assignment(line->tokens);
			cout << line->index << '\n'; //testing
			line->changed = false;
			Scope a = make_full_scope(lines, line->index);
			Scope local_scope;
			line -> answer = interpret(line->tokens, local_scope, a);
			line->scope = local_scope;
			if(line->assign){
				//dependency chain cascade here
				for(Line *other : lines){
					if(other == line) continue;
					for(const auto &entry : line->scope.variables){
						if(other->scope.dependencies.count(entry.first)){
							other->changed = true;
							break;
						}
					}
				}
			} else {
				//not sure why i added else but im assuming past me wasnt stupid and this is here for a reason
			}
		}
	}
}