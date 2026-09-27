#pragma once

#include <string>
#include <vector>
#include "token.h"
#include "scope.h"

using namespace std;

string interpret(const vector<Token> &tokens, Scope &local_scope, Scope &scope);
