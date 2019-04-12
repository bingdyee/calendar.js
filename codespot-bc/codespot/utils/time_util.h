/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-12
==============================================================================*/


#ifndef CODESPOT_UTILS_TIMEUTIL_H_
#define CODESPOT_UTILS_TIMEUTIL_H_

#include<chrono> 

using namespace std::chrono;

namespace codespot {

class Timer {
public:

	Timer() : m_begin(std::chrono::high_resolution_clock::now()) {}

	void reset() { m_begin = std::chrono::high_resolution_clock::now(); }

	// default millisecond 
	int64_t elapsed() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
	}
	// microsecond 
	int64_t elapsed_micro() const {
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	// nanosecond 
	int64_t elapsed_nano() const {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	// second  
	int64_t elapsed_seconds() const {
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	// minute 
	int64_t elapsed_minutes() const {
		return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	// hour  
	int64_t elapsed_hours() const {
		return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

private:
	std::chrono::time_point<high_resolution_clock> m_begin;
};

} // end namespace codespot


#endif // !CODESPOT_UTILS_LOGGER_H_
