#pragma once
#include "Logger.h"

#include "ETokenType.h"

class LexicalValidator
{
private:
    Logger m_logger;

public:
    LexicalValidator();
    bool IsValidNumber(std::string str);
    bool IsValidChar(char c);
    bool IsValidStartingChar(char c);
    bool IsValidName(std::string str);
    bool IsOperator(ETokenType t);
};