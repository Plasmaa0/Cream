#include "Logger.h"

void Logger::Log(const std::string message, ELogLevel level)
{
    if (level < m_LogLevel)
        return;
    std::string msg(message);
    std::string ColorEscapeCode = Colors[level];
    std::string LogLevelName = LogLevelNames[level];
    std::string ToOutput = m_name + ":" + ColorEscapeCode + "[" + LogLevelName + ":" + msg + "]" + ResetColorCode;
    std::cout << ToOutput << std::endl;
}

void Logger::Test()
{
    Log("Test Message", TRACE);
    Log("Test Message", DEBUG);
    Log("Test Message", INFO);
    Log("Test Message", WARNING);
    Log("Test Message", ERROR);
    Log("Test Message", FATAL);
}

Logger::Logger(ELogLevel LogLevel, std::string name) : m_LogLevel(LogLevel), m_name(name)
{
    ;
}

Logger::Logger(std::string name) : m_LogLevel(m_defaultLogLevel), m_name(name)
{
    ;
}

void Logger::SetLogLevel(int logLevel)
{
    Log("LogLevel changed to " + std::to_string(logLevel), TRACE);
    m_LogLevel = logLevel;
}
