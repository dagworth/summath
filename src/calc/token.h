#pragma once

#include <string>

enum class TokenType {
    Number,
    Identifier,

    Def,
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

    True,
    False,

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

    Greater,
    GreaterEq,
    Less,
    LessEq,

    CompareAnd,
    CompareOr,
    CompareNAnd,
    Not,

    Comma
};

struct Token {
    TokenType type;
    std::string value;
    // int line = 0;
};