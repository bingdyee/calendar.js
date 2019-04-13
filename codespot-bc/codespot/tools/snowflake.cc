/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-12
==============================================================================*/

#include <iostream>
#include <exception>
#include <stdexcept>
#include <chrono>
#include <sstream>

#include "codespot/tools/snowflake.h"

namespace codespot {

SnowflakeWorker::SnowflakeWorker(uint64_t workerId, uint64_t datacenterId) {
	if (workerId > maxWorkerId || workerId < 0) {
		std::ostringstream str;
		str << "worker Id can't be greater than " << workerId << " or less than 0";
		throw std::invalid_argument(str.str());
	}
	if (datacenterId > maxDatacenterId || datacenterId < 0) {
		std::ostringstream str;
		str << "datacenter Id can't be greater than " << datacenterId << " or less than 0";
		throw std::invalid_argument(str.str());
	}
	this->workerId = workerId;
	this->datacenterId = datacenterId;
}

SnowflakeWorker::~SnowflakeWorker() { }

uint64_t SnowflakeWorker::nextId() {
	std::unique_lock<std::mutex> lock{ mutex };
	uint64_t timestamp = currentMillis();
	if (timestamp < lastTimestamp) {
		std::ostringstream str;
		str << "Clock moved backwards.  Refusing to generate id for " << timestamp << " milliseconds";
		throw std::exception(std::runtime_error(str.str()));
	}
	if (lastTimestamp == timestamp) {
		sequence = (sequence + 1) & sequenceMask;
		if (sequence == 0) {
			timestamp = nextMillis(lastTimestamp);
		}
	}
	else {
		sequence = 0L;
	}
	lastTimestamp = timestamp;
	uint64_t result = ((timestamp - twepoch) << timestampLeftShift)
		| (datacenterId << datacenterIdShift)
		| (workerId << workerIdShift)
		| sequence;
	// std::cout << result << std::endl;
	return result;
}

uint64_t SnowflakeWorker::nextMillis(uint64_t lastTimestamp) {
	uint64_t timestamp = currentMillis();
	while (timestamp <= lastTimestamp) {
		timestamp = currentMillis();
	}
	return timestamp;
}

uint64_t SnowflakeWorker::currentMillis() {
	return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
}

} // end namespace codespot