#pragma once

#include <iostream>

typedef enum ELogLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
} ELogLevel;

/*
namespace DefaultLogLevels
{
    ELogLevel Lexer = TRACE;
    ELogLevel LexicalValidator = TRACE;
    ELogLevel Reader = TRACE;
    ELogLevel Token = TRACE;
    ELogLevel Tokenizer = TRACE;
} // namespace DefaultLogLevels
*/

class Logger
{
private:
    ELogLevel m_defaultLogLevel = DEBUG;
    int m_LogLevel;
    std::string m_name;
    const char LogLevelNames[6][20] = {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
        "FATAL"};

    std::string Colors[6] = {
        "\033[90m",
        "\033[97m",
        "\033[96m",
        "\033[92m",
        "\033[93m",
        "\033[91m"};

    std::string ResetColorCode = "\x1b[0m";

public:
    Logger(ELogLevel LogLevel, std::string name);
    Logger(std::string name);
    void SetLogLevel(int logLevel);
    void Log(const std::string message, ELogLevel level = ELogLevel::INFO);
    void Test();
};