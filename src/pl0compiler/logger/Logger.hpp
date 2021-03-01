#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <deque>

namespace pl0compiler { namespace logger {

class Logger
{
public:
	enum Level
	{
		Error,
		Info,
		Debug
	};

    void write(std::string str);
    void write(std::deque<char> bin);
};

} }
