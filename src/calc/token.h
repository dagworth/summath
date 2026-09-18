#pragma once

#include <string>

enum class TokenType {
    Number,
    Identifier,

    Function,
    For,
    While,
    Bool,
    If,
    End,
    EndLine,
    Do,
    Then,

    Sin,
    Cos,
    Pi,

    DegToRad,
    RadToDeg,

    AssignAdd,
    AssignSub,
    AssignDiv,
    AssignMul,
    AssignMod,
    AssignPow,

    AssignAddOne,
    AssignSubOne,

    Neg,
    Add,
    Div,
    Mul,
    Mod,
    Pow,

    LParen,
    RParen,

    Equals,
    Assign,

    CompareAnd,
    CompareOr,
    CompareNAnd,
    Not
};

struct Token {
    TokenType type;
    std::string value;
};