#include "Reader.h"
Reader::Reader(std::string FileName) : m_is(FileName), m_logger("ReaderLogger")
{
    ;
}

std::string Reader::GetLine()
{
    std::string s;
    s.clear();
    if (IsReadable())
    {
        getline(m_is, s);
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