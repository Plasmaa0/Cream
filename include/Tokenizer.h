#pragma once

#include "LexicalValidator.h"
#include "Logger.h"
#include "Token.h"

class Tokenizer
{
private:
    Logger m_logger;
    LexicalValidator m_validator;
    ETokenType Single(std::string &str);
    ETokenType Double(std::string &str);
    ETokenType Triple(std::string &str);
    ETokenType Keyword(std::string &str);
    ETokenType Name(std::string &str);
    ETokenType Number(std::string &str);

public:
    Tokenizer();
    Token Tokenize(std::string str);
};