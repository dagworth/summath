#pragma once

#include "token.h"
#include <string>
#include <vector>

using namespace std;

bool is_digit(char c);
bool is_number(char c);
bool is_alpha(char c);
bool is_keyword(string str);
TokenType keyword_to_token(string str);
bool is_assignment(TokenType t);
bool has_assignment(vector<Token> tokens);