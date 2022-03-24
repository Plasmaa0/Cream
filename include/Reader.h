#pragma once

#include "Logger.h"
#include <fstream>
#include <iostream>

class Reader
{
private:
    std::ifstream m_is;
    Logger m_logger;

public:
    Reader(std::string FileName);
    std::string GetLine();
    bool IsOpen();
    bool IsReachedEnd();
    bool IsReadable();
};