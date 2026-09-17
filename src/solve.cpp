#include "calc/lexer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string solve(const string &str){
	// stringstream input(str);
	vector<Token> lexed = lex(str);

	// while (getline(input, line, '\n')) {
	// 	lexed << lex(line) << '\n';
	// }

	return "";
}