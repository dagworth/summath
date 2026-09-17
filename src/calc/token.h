#pragma once

#include <string>

enum class TokenType {
    Number,
    Operater, //+,-,/,*
    Identifier, //variable
    Function,
    For,
    While,
    Bool,
    Comparator, // < > >= && || !=
    Assign, //= ++ += -- -= /= %= *=
    If,
    End,
    EndLine,
    Sin,
    Cos,
    Pi,
    DegToRad,
    RadToDeg,
    AssignAdd
};

struct Token {
    TokenType type;
    std::string value;
};