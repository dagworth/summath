#include "calc/lexer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string solve(const string &str){
	vector<Token> lexed = lex(str);
	int result = system("clear");
	for (const Token &token : lexed) {
		cout << "token: " << token.value << "\n";
	}
	return to_string(lexed.size());
}