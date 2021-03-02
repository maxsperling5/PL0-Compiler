/************************/
/* Author: Max Sperling */
/************************/

#include "Logger.hpp"

#include <iostream>

namespace pl0compiler { namespace common {

Logger::Logger(const Level level) : m_level(level) {}

void Logger::error(const std::string &str)
{
    write(Level::Error, str);
}

void Logger::info(const std::string &str)
{
    write(Level::Info, str);
}

void Logger::debug(const std::string &str)
{
    write(Level::Debug, str);
}

void Logger::write(Level level, const std::string &str)
{
	if (allowed(level)) { std::cout << str << std::endl; }
}

bool Logger::allowed(Level level)
{
	return (m_level >= level);
}

} }
