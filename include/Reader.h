#pragma once

#include "Logger.h"
#include <fstream>
#include <iostream>

class Reader
{
private:
    std::ifstream m_is;
    Logger m_logger;
    std::istream &m_cin;
    bool m_fileMode;

public:
    Reader(std::string FileName);
    Reader(std::istream &is);
    std::string GetLine();
    bool IsOpen();
    bool IsReachedEnd();
    bool IsReadable();
};