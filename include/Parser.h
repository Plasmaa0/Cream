#pragma once

#include "AbstractSyntaxTree.h"
#include "Token.h"
#include <iostream>
#include <vector>

class Parser
{
private:
public:
    Parser();
    AbstractSyntaxTree parseTokenArray(std::vector<Token> TokenArray);
};