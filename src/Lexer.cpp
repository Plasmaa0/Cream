#include "Lexer.h"

Lexer::Lexer(std::string FileName) : m_logger("LexerLogger"), m_reader(FileName), m_fileMode(true)
{
    ;
}

Lexer::Lexer(std::istream &is) : m_logger("LexerLogger"), m_reader(is), m_fileMode(false)
{
    ;
}

std::vector<Token> Lexer::GetRawTokensArray()
{
    std::vector<Token> tokens;
    std::string line;
    while (m_reader.IsReadable() or (not m_fileMode))
    {
        line = m_reader.GetLine();
        if (line == "exit")
        {
            break;
        }

        std::string tok_str;
        for (auto &&digit : line)
        {
            tok_str += digit;
            Token t = m_tokenizer.Tokenize(tok_str);
            tok_str.clear();
            if (t.GetType() == COMMENT)
            {
                break;
            }
            tokens.push_back(t);
        }
        tokens.push_back(Token(NEWLINE));
    }
    return tokens;
}

std::vector<Token> Lexer::ParseStrings(std::vector<Token> TokensArray)
{
    auto isParentesis = [](auto t)
    { return t.GetType() == INVALID and t.HaveContents() and t.GetContents() == "\""; };

    std::vector<Token> stringsParsed;
    std::string str;
    bool stringStarted = isParentesis(TokensArray[0]);
    for (auto &&tok : TokensArray)
    {
        if (isParentesis(tok))
        {
            if (stringStarted)
            {
                stringStarted = false;
                stringsParsed.push_back(Token(STRING, str));
                str.clear();
            }
            else
            {
                stringStarted = true;
            }
        }
        else
        {
            if (stringStarted)
            {
                str += tok.GetContents();
            }
            else
            {
                stringsParsed.push_back(tok);
            }
        }
    }
    if (stringStarted)
    {
        m_logger.Log("String Parentesis pairing error", FATAL);
    }

    return stringsParsed;
}

std::vector<Token> Lexer::ParseNames(std::vector<Token> TokensArray)
{
    std::vector<Token> namesParsed;
    std::string name;
    bool nameStarted = (TokensArray[0].GetType() == NAME);
    for (auto &&tok : TokensArray)
    {
        if (tok.GetType() == NAME)
        {
            name.append(tok.GetContents());
            if (!nameStarted)
            {
                nameStarted = true;
            }
        }
        else
        {
            if (nameStarted)
            {
                namesParsed.push_back(m_tokenizer.Tokenize(name));
                name.clear();
                nameStarted = false;
            }
            namesParsed.push_back(tok);
        }
    }
    return namesParsed;
}

std::vector<Token> Lexer::ParseNumbers(std::vector<Token> TokensArray)
{
    std::vector<Token> numbersParsed;
    std::string number;
    bool numberStarted = (TokensArray[0].GetType() == NUMBER || TokensArray[0].GetType() == DOT);
    for (auto &&tok : TokensArray)
    {
        if (tok.GetType() == NUMBER || tok.GetType() == DOT)
        {
            number.append(tok.GetContents());
            if (!numberStarted)
            {
                numberStarted = true;
            }
        }
        else
        {
            if (numberStarted)
            {
                numbersParsed.push_back(m_tokenizer.Tokenize(number));
                number.clear();
                numberStarted = false;
            }
            numbersParsed.push_back(tok);
        }
    }
    return numbersParsed;
}

std::vector<Token> Lexer::ParseMultidigitOperators(std::vector<Token> TokensArray)
{
    std::vector<Token> twoDigitParsed;
    for (size_t i = 0; i < TokensArray.size(); i++)
    {
        if (not m_validator.IsOperator(TokensArray[i].GetType()))
        {
            twoDigitParsed.push_back(TokensArray[i]);
            continue;
        }
        if (not m_validator.IsOperator(TokensArray[i + 1].GetType()))
        {
            twoDigitParsed.push_back(TokensArray[i]);
            continue;
        }
        switch (TokensArray[i].GetType())
        {
        case EQUAL:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(EQEQ));
                i++;
            }
            break;
        case EXCL:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(NEQ));
                i++;
            }
            break;
        case LESS:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(LEQUAL));
                i++;
            }
            if (TokensArray[i + 1].GetType() == LESS)
            {
                twoDigitParsed.push_back(Token(LSHIFT));
                i++;
            }
            break;
        case GREATER:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(GREQUAL));
                i++;
            }
            if (TokensArray[i + 1].GetType() == GREATER)
            {
                twoDigitParsed.push_back(Token(RSHIFT));
                i++;
            }
            break;
        case PLUS:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(PLUSEQ));
                i++;
            }
            if (TokensArray[i + 1].GetType() == PLUS)
            {
                twoDigitParsed.push_back(Token(INCREMENT));
                i++;
            }
            break;
        case MINUS:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(MINUSEQ));
                i++;
            }
            if (TokensArray[i + 1].GetType() == MINUS)
            {
                twoDigitParsed.push_back(Token(DECREMENT));
                i++;
            }
            break;
        case STAR:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(STAREQ));
                i++;
            }
            if (TokensArray[i + 1].GetType() == STAR)
            {
                twoDigitParsed.push_back(Token(DOUBLESTAR));
                i++;
            }
            break;
        case SLASH:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(SLASHEQ));
                i++;
            }
            if (TokensArray[i + 1].GetType() == SLASH)
            {
                twoDigitParsed.push_back(Token(DSLASH));
                i++;
            }
            break;
        case PERCENT:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(PERCENTEQ));
                i++;
            }
            break;
        case AMPER:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(AMPEREQ));
                i++;
            }
            break;
        case VBAR:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(VBAREQ));
                i++;
            }
            break;
        case CIRCUMFLEX:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(CIRCUMFLEXEQ));
                i++;
            }
            break;
        case AT:
            if (TokensArray[i + 1].GetType() == EQUAL)
            {
                twoDigitParsed.push_back(Token(ATEQ));
                i++;
            }
            break;
        case DOT:
            std::cout << "FIXME DOT FIXME DOT FIXME DOT FIXME DOT FIXME DOT FIXME DOT" << std::endl;
            break;

        default:
            break;
        }
    }
    // 1st: = ! < < < > > > + + - - * * * / / / % & | ^ @ .
    // 2nd: = = = < < = > > = + = - = * * = / / = = = = = .
    // 3rd:         =     =             =     =           .
    std::vector<Token> threeDigitsParsed;

    for (size_t i = 0; i < twoDigitParsed.size(); i++)
    {
        if (not m_validator.IsOperator(twoDigitParsed[i].GetType()))
        {
            threeDigitsParsed.push_back(twoDigitParsed[i]);
            continue;
        }
        if (not m_validator.IsOperator(twoDigitParsed[i + 1].GetType()))
        {
            threeDigitsParsed.push_back(twoDigitParsed[i]);
            continue;
        }
        switch (twoDigitParsed[i].GetType())
        {
        case LSHIFT:
            if (twoDigitParsed[i + 1].GetType() == EQUAL)
            {
                threeDigitsParsed.push_back(Token(LSHIFTEQ));
                i++;
            }
            break;
        case RSHIFT:
            if (twoDigitParsed[i + 1].GetType() == EQUAL)
            {
                threeDigitsParsed.push_back(Token(RSHIFTEQ));
                i++;
            }
            break;
        case DOUBLESTAR:
            if (twoDigitParsed[i + 1].GetType() == EQUAL)
            {
                threeDigitsParsed.push_back(Token(DOUBLESTAREQ));
                i++;
            }
            break;
        case DSLASH:
            if (twoDigitParsed[i + 1].GetType() == EQUAL)
            {
                threeDigitsParsed.push_back(Token(DSLASHEQ));
                i++;
            }
            break;
        case DOT:
            std::cout << "FIXME DOT FIXME DOT FIXME DOT FIXME DOT FIXME DOT FIXME DOT" << std::endl;
            break;

        default:
            break;
        }
    }
    return threeDigitsParsed;
}

std::vector<Token> Lexer::GetTokenArray()
{
    m_logger.Log("Started lexical analyzis.", DEBUG);
    std::vector<Token> rawTokensArray = GetRawTokensArray();
    m_logger.Log("Got RAW tokens.", DEBUG);
    std::vector<Token> namesParsed = ParseNames(rawTokensArray);
    m_logger.Log("Parsed names.", DEBUG);
    std::vector<Token> numbersParsed = ParseNumbers(namesParsed);
    m_logger.Log("Parsed numbers.", DEBUG);
    std::vector<Token> multidigitOperatorsParsed = ParseMultidigitOperators(numbersParsed);
    m_logger.Log("Parsed operators.", DEBUG);
    std::vector<Token> stringsParsed = ParseStrings(multidigitOperatorsParsed);
    m_logger.Log("Parsed strings.", DEBUG);
    return stringsParsed;
}
