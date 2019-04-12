/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-12
==============================================================================*/


#ifndef CODESPOT_UTILS_SNOWFLAKE_H_
#define CODESPOT_UTILS_SNOWFLAKE_H_

#include <mutex>
#include <atomic>

#include "codespot/utils/common.h"

namespace codespot {

class SnowflakeWorker : NonCopyable {
public:
	SnowflakeWorker(uint64_t workerId = 1, uint64_t datacenterId = 1);
	~SnowflakeWorker();

	uint64_t nextId();

private:

	uint64_t nextMillis(uint64_t lastTimestamp);
	uint64_t currentMillis();

	const uint64_t twepoch = 1420041600000L;
	const uint32_t workerIdBits = 5L;
	const uint32_t datacenterIdBits = 5L;
	const uint32_t maxWorkerId = -1L ^ (-1L << workerIdBits);
	const uint32_t maxDatacenterId = -1L ^ (-1L << datacenterIdBits);
	const uint32_t sequenceBits = 12L;
	const uint32_t workerIdShift = sequenceBits;
	const uint32_t datacenterIdShift = sequenceBits + workerIdBits;
	const uint32_t timestampLeftShift = sequenceBits + workerIdBits + datacenterIdBits;
	const uint32_t sequenceMask = -1L ^ (-1L << sequenceBits);

	uint32_t workerId;
	uint32_t datacenterId;
	std::atomic<uint32_t> sequence = 0L;
	uint64_t lastTimestamp = 0L;
	std::mutex mutex;

};

} // end namespace codespot

#endif //!CODESPOT_UTILS_SNOWFLAKE_H_