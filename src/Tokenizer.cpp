#include "Tokenizer.h"

Tokenizer::Tokenizer() : m_logger("TokenizerLogger"), m_validator()
{
    ;
}

Token Tokenizer::Tokenize(std::string str)
{
    if (str.length() == 0)
        return Token(INVALID);
    m_logger.Log("trying keyword", TRACE);
    ETokenType t = Keyword(str);
    if (t == ETokenType::INVALID)
    {
        m_logger.Log("trying name", TRACE);
        t = Name(str);
        if (t == ETokenType::INVALID)
        {
            m_logger.Log("trying number", TRACE);
            t = Number(str);
        }
    }
    if (t != ETokenType::INVALID)
    {
        if (t == ETokenType::NAME or t == ETokenType::NUMBER)
        {
            return Token(t, str);
        }
        return Token(t, str); // keyword token
    }
    switch (str.length())
    {
    case 1:
        m_logger.Log("trying 1", TRACE);
        t = Single(str);
        break;
    case 2:
        m_logger.Log("trying 2", TRACE);
        t = Double(str);
        break;
    case 3:
        m_logger.Log("trying 3", TRACE);
        t = Triple(str);
        break;
    }
    return Token(t, str);
}

ETokenType Tokenizer::Keyword(std::string &str)
{
    if (str == "if")
        return ETokenType::IF;
    if (str == "else")
        return ETokenType::ELSE;
    if (str == "for")
        return ETokenType::FOR;
    if (str == "def ")
        return ETokenType::FUNCDECL;
    if (str == "return")
        return ETokenType::RETURN;
    if (str == "import")
        return ETokenType::IMPORT;
    return ETokenType::INVALID;
}

ETokenType Tokenizer::Name(std::string &str)
{
    if (m_validator.IsValidName(str))
        return ETokenType::NAME;
    else
        return ETokenType::INVALID;
}

ETokenType Tokenizer::Number(std::string &str)
{
    if (m_validator.IsValidNumber(str))
        return ETokenType::NUMBER;
    else
        return ETokenType::INVALID;
}

ETokenType Tokenizer::Single(std::string &str)
{
    switch (str[0])
    {
    case ' ':
        return ETokenType::SPACE;
        break;
    case '\n':
        return ETokenType::NEWLINE;
        break;
    case '\t':
        return ETokenType::INDENT;
        break;
    case '\0':
        return ETokenType::END;
        break;
    case '(':
        return ETokenType::LB;
        break;
    case ')':
        return ETokenType::RB;
        break;
    case '[':
        return ETokenType::LSQB;
        break;
    case ']':
        return ETokenType::RSQB;
        break;
    case '{':
        return ETokenType::LFIGB;
        break;
    case '}':
        return ETokenType::RFIGB;
        break;
    case ':':
        return ETokenType::COLON;
        break;
    case ',':
        return ETokenType::COMMA;
        break;
    case ';':
        return ETokenType::SEMI;
        break;
    case '.':
        return ETokenType::DOT;
        break;
    case '+':
        return ETokenType::PLUS;
        break;
    case '-':
        return ETokenType::MINUS;
        break;
    case '*':
        return ETokenType::STAR;
        break;
    case '^':
        return ETokenType::CIRCUMFLEX;
        break;
    case '~':
        return ETokenType::TILDE;
        break;
    case '/':
        return ETokenType::SLASH;
        break;
    case '|':
        return ETokenType::VBAR;
        break;
    case '&':
        return ETokenType::AMPER;
        break;
    case '@':
        return ETokenType::AT;
        break;
    case '<':
        return ETokenType::LESS;
        break;
    case '>':
        return ETokenType::GREATER;
        break;
    case '=':
        return ETokenType::EQUAL;
        break;
    case '!':
        return ETokenType::EXCL;
        break;
    case '%':
        return ETokenType::PERCENT;
        break;
    case '#':
        return ETokenType::COMMENT;
        break;
    default:
        return ETokenType::INVALID;
        break;
    }
}

ETokenType Tokenizer::Double(std::string &str)
{
    switch (str[0])
    {
    case '+':
        switch (str[1])
        {
        case '=':
            return ETokenType::PLUSEQ;
            break;
        case '+':
            return ETokenType::INCREMENT;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '-':
        switch (str[1])
        {
        case '=':
            return ETokenType::MINUSEQ;
            break;
        case '-':
            return ETokenType::DECREMENT;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '*':
        switch (str[1])
        {
        case '=':
            return ETokenType::STAREQ;
            break;
        case '*':
            return ETokenType::DOUBLESTAR;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '^':
        switch (str[1])
        {
        case '=':
            return ETokenType::CIRCUMFLEXEQ;
            break;
        case '*':
            return ETokenType::DOUBLESTAR;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '/':
        switch (str[1])
        {
        case '=':
            return ETokenType::SLASHEQ;
            break;
        case '/':
            return ETokenType::DSLASH;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '|':
        switch (str[1])
        {
        case '=':
            return ETokenType::VBAREQ;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '&':
        switch (str[1])
        {
        case '=':
            return ETokenType::AMPEREQ;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '@':
        switch (str[1])
        {
        case '=':
            return ETokenType::ATEQ;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '<':
        switch (str[1])
        {
        case '=':
            return ETokenType::LEQUAL;
            break;
        case '<':
            return ETokenType::LSHIFT;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '>':
        switch (str[1])
        {
        case '=':
            return ETokenType::GREQUAL;
            break;
        case '<':
            return ETokenType::RSHIFT;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '=':
        switch (str[1])
        {
        case '=':
            return ETokenType::EQEQ;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    case '%':
        switch (str[1])
        {
        case '=':
            return ETokenType::PERCENTEQ;
            break;
        default:
            return ETokenType::INVALID;
            break;
        }
        break;
    default:
        return ETokenType::INVALID;
        break;
    }
}

ETokenType Tokenizer::Triple(std::string &str)
{
    switch (str[0])
    {
    case '*':
        switch (str[1])
        {
        case '*':
            switch (str[2])
            {
            case '=':
                return ETokenType::DOUBLESTAREQ;
            }
            break;
        }
        break;
    case '.':
        switch (str[1])
        {
        case '.':
            switch (str[2])
            {
            case '.':
                return ETokenType::ELLIPSIS;
            }
            break;
        }
        break;
    case '/':
        switch (str[1])
        {
        case '/':
            switch (str[2])
            {
            case '=':
                return ETokenType::DSLASHEQ;
            }
            break;
        }
        break;
    case '<':
        switch (str[1])
        {
        case '<':
            switch (str[2])
            {
            case '=':
                return ETokenType::LSHIFTEQ;
            }
            break;
        }
        break;
    case '>':
        switch (str[1])
        {
        case '>':
            switch (str[2])
            {
            case '=':
                return ETokenType::RSHIFTEQ;
            }
            break;
        }
        break;
    default:
        return ETokenType::INVALID;
        break;
    }
    return ETokenType::INVALID;
}
