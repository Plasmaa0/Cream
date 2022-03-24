#include "Cream.h"

Cream::Cream() : m_lexer(std::cin), m_fileMode(false)
{
}

Cream::Cream(std::string FileName) : m_lexer(FileName), m_fileMode(true)
{
}

void Cream::run()
{
    std::vector<Token> tokens = m_lexer.GetTokenArray();
    for (auto &&tok : tokens)
    {
        std::cout << TokenNames[tok.GetType()];
        if (tok.HaveContents())
        {
            std::cout << ' ' << tok.GetContents();
        }
        std::cout << std::endl;
    }
}
