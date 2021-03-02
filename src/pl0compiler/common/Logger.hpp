#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <deque>

namespace pl0compiler { namespace common {

class Logger
{
public:
	enum class Level
	{
		Error,
		Info,
		Debug
	};

	Logger(const Level level);

	void error(const std::string &str);
    void info(const std::string &str);
    void debug(const std::string &str);

    void write(Level level, const std::string &str);

private:
	bool allowed(Logger::Level level);

	const Level m_level;
};

} }
