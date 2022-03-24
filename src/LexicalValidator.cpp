#include "LexicalValidator.h"

LexicalValidator::LexicalValidator() : m_logger("LexicalValidatorLogger")
{
    ;
}

bool LexicalValidator::IsValidNumber(std::string str)
{
    // for (auto &&digit : str)
    // {
    //     if (not('0' <= digit and digit <= '9'))
    //     {
    //         return false;
    //     }

    // }

    int DotCount = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        bool IsDot = str[i] == '.';
        bool IsNum = ('0' <= str[i] and str[i] <= '9');
        if (IsDot)
            DotCount++;
        if (not((IsNum or IsDot) and DotCount <= 1))
        {
            m_logger.Log("err: '" + std::to_string(str[i]) + "'", TRACE);
            return false;
        }
    }
    return true;
}

bool LexicalValidator::IsValidChar(char c)
{
    return (
        ('a' <= c and c <= 'z') or
        ('A' <= c and c <= 'Z') or
        ('0' <= c and c <= '9') or
        (c == '_'));
}
bool LexicalValidator::IsValidStartingChar(char c)
{
    return (
        ('a' <= c and c <= 'z') or
        ('A' <= c and c <= 'Z') or
        (c == '_'));
}

bool LexicalValidator::IsValidName(std::string str)
{
    if (IsValidStartingChar(str[0]))
    {
        for (int i = 1; str[i] != '\0'; i++)
        {
            if (not IsValidChar(str[i]))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool LexicalValidator::IsOperator(ETokenType t)
{
    return t == PLUS or
           t == MINUS or
           t == STAR or
           t == DOUBLESTAR or
           t == CIRCUMFLEX or
           t == TILDE or
           t == SLASH or
           t == DSLASH or
           t == VBAR or
           t == AMPER or
           t == AT or
           t == LESS or
           t == GREATER or
           t == EQUAL or
           t == PERCENT or
           t == EQEQ or
           t == EXCL or
           t == NEQ or
           t == LEQUAL or
           t == GREQUAL or
           t == LSHIFT or
           t == RSHIFT or
           t == PLUSEQ or
           t == MINUSEQ or
           t == STAREQ or
           t == SLASHEQ or
           t == PERCENTEQ or
           t == AMPEREQ or
           t == VBAREQ or
           t == CIRCUMFLEXEQ or
           t == LSHIFTEQ or
           t == RSHIFTEQ or
           t == DOUBLESTAREQ or
           t == DSLASHEQ or
           t == ATEQ or
           t == INCREMENT or
           t == DECREMENT;
}