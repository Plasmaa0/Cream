#pragma once

#include "Lexer.h"
#include "Parser.h"

class Cream
{
private:
    Lexer m_lexer;
    bool m_fileMode;
    Parser m_parser;

public:
    Cream();
    Cream(std::string FileName);
    void run();
};