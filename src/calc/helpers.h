#pragma once

#include "token.h"
#include <string>

bool is_digit(char c);
bool is_number(char c);
bool is_alpha(char c);
bool is_keyword(std::string str);
TokenType keyword_to_token(std::string str);