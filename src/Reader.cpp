#include "Reader.h"
Reader::Reader(std::string FileName) : m_is(FileName), m_logger("ReaderLogger"), m_cin(std::cin), m_fileMode(true)
{
    m_logger.Log("Initialized in FILE_MODE", DEBUG);
}

Reader::Reader(std::istream &is) : m_is(), m_logger("ReaderLogger"), m_cin(is), m_fileMode(false)
{
    m_logger.Log("Initialized in INTERACTIVE_MODE", DEBUG);
}

std::string Reader::GetLine()
{
    std::string s;
    s.clear();
    if (m_fileMode)
    {
        if (IsReadable())
        {
            m_logger.Log("Got FILE line", TRACE);
            getline(m_is, s);
        }
    }
    else
    {
        m_logger.Log("Got INTERACTIVE line", TRACE);
        std::cout << ">>> ";
        getline(m_cin, s);
    }
    return s;
}

bool Reader::IsOpen()
{
    return m_is.is_open();
}

bool Reader::IsReachedEnd()
{
    return m_is.eof();
}

bool Reader::IsReadable()
{
    return IsOpen() and (not IsReachedEnd());
}