#include "Token.h"

Token::Token(ETokenType type) : m_type(type)
{
    ;
}
Token::Token(ETokenType type, std::string &contents) : m_type(type), m_contents(contents)
{
    ;
}

Token::Token(const Token &other)
{
    if (&other == this)
    {
        return;
    }
    m_type = other.m_type;
    if (other.HaveContents())
    {
        m_contents = other.m_contents;
    }
}

bool Token::HaveContents() const
{
    return m_type == ETokenType::FOR or
           m_type == ETokenType::IF or
           m_type == ETokenType::ELSE or
           m_type == ETokenType::FUNCDECL or
           m_type == ETokenType::NAME or
           m_type == ETokenType::NUMBER or
           m_type == ETokenType::INVALID or
           m_type == ETokenType::STRING or
           m_type == ETokenType::RETURN;
}

ETokenType Token::GetType() const
{
    return m_type;
}

const std::string Token::GetContents() const
{
    return m_contents;
}

Token &Token::operator=(Token &&other)
{
    m_type = other.m_type;
    if (other.HaveContents())
    {
        m_contents = other.m_contents;
    }
    return *this;
}
