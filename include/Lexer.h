#pragma once

#include "LexicalValidator.h"
#include "Logger.h"
#include "Reader.h"
#include "Tokenizer.h"
#include <iostream>
#include <vector>

class Lexer
{
private:
    Logger m_logger;
    Reader m_reader;
    Tokenizer m_tokenizer;
    LexicalValidator m_validator;
    bool m_fileMode;
    std::vector<Token> GetRawTokensArray();
    std::vector<Token> ParseStrings(std::vector<Token> TokensArray);
    std::vector<Token> ParseNames(std::vector<Token> TokensArray);
    std::vector<Token> ParseNumbers(std::vector<Token> TokensArray);
    std::vector<Token> ParseMultidigitOperators(std::vector<Token> TokensArray);

public:
    Lexer(std::string FileName);
    Lexer(std::istream &is);
    std::vector<Token> GetTokenArray();
};