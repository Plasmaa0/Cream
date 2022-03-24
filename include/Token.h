#pragma once

#include "ETokenType.h"
#include "Logger.h"
#include <cctype>
#include <cstring>
#include <iostream>
class Token
{
private:
    const short m_tokenContentsSize = 64;
    ETokenType m_type;
    std::string m_contents;

public:
    Token(ETokenType type);
    Token(const Token &other);
    Token(ETokenType type, std::string &contents);
    bool HaveContents() const;
    ETokenType GetType() const;
    const std::string GetContents() const;
    Token &operator=(Token &&other);
};

const std::string TokenNames[] = {
    "NAME",
    "SPACE",
    "NUMBER",
    "STRING",
    "\\n",
    "\\t",
    "END",
    "(",
    ")",
    "[",
    "]",
    "{",
    "}",
    ":",
    ",",
    ";",
    ".",
    "+",
    "-",
    "*",
    "**",
    "^",
    "~",
    "/",
    "//",
    "|",
    "&",
    "@",
    "<",
    ">",
    "=",
    "%",
    "==",
    "!",
    "!=",
    "<=",
    ">=",
    "<<",
    ">>",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^=",
    "<<=",
    ">>=",
    "**=",
    "//=",
    "@=",
    "...",
    "COMMENT",
    "++",
    "--",
    "FOR",
    "IF",
    "ELSE",
    "FUNCDECL",
    "RETURN",
    "IMPORT",
    "INVALID"};