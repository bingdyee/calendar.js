/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-12
==============================================================================*/


#ifndef CODESPOT_UTILS_LOGGER_H_
#define CODESPOT_UTILS_LOGGER_H_

#include <iostream>
#include <sstream>

#include "codespot/utils/common.h"


namespace codespot {

// logging level
const int INFO = 0;
const int WARNING = 1;
const int ERROR = 2;
const int FATAL = 3;

namespace {

class Logger : public std::basic_ostringstream<char> {

public:
	Logger(const char* filename, int line, int level);
	~Logger();

private:
	void PrintMessage();

	int level;
	const char* filename;
	int line;
};

Logger::Logger(const char* filename, int line, int level) : level(level), filename(filename), line(line) { }

Logger::~Logger() {
	PrintMessage();
}

void Logger::PrintMessage() {

	std::cout << FormatCurrentTime("[%Y-%m-%d %H:%M:%S]");
	switch (level) {
	case INFO:
		std::cout << "INFO:";
		break;
	case WARNING:
		std::cout << "WARNING:";
		break;
	case ERROR:
		std::cout << "ERROR:";
		break;
	case FATAL:
		std::cout << "FATAL: ";
		break;
	default:break;
	}
	std::cout << filename << "[" << line << "]>> " << this->str() << std::endl;
}


#define _AC_LOG_INFO Logger(__FILE__, __LINE__, INFO)
#define _AC_LOG_WARNING Logger(__FILE__, __LINE__, WARNING)
#define _AC_LOG_ERROR Logger(__FILE__, __LINE__, ERROR)
#define _AC_LOG_FATAL Logger(__FILE__, __LINE__, FATAL)

} // end empty namespace

#define LOG(level) _AC_LOG_##level


} // end namespace codespot

#endif // !CODESPOT_UTILS_LOGGER_H_