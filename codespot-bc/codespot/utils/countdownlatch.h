/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-12
==============================================================================*/


#ifndef CODESPOT_UTILS_COUNTDOWNLATCH_H_
#define CODESPOT_UTILS_COUNTDOWNLATCH_H_

#include <inttypes.h>
#include <stdint.h>
#include <mutex>
#include <thread>
#include <iostream>
#include <functional>
#include <condition_variable>


#include "codespot/utils/common.h"

namespace codespot {

class Countdownlatch : NonCopyable {
public:
	Countdownlatch(int count) : count(count) {}
	~Countdownlatch() {
		while (!threads.empty()) {
			delete threads.back(), threads.pop_back();
		}
	}

	void await(uint64_t nanosecs = 0) {
		std::unique_lock<std::mutex> lck(lock);
		if (count != 0) {
			if (nanosecs > 0) {
				cv.wait_for(lck, std::chrono::nanoseconds(nanosecs));
			} else {
				cv.wait(lck);
			}
		}
	}

	void countDown() {
		std::unique_lock<std::mutex> lck(lock);
		if (count != 0) {
			--count;
			if (count == 0) {
				cv.notify_all();
			}
		}
	}

	int getCount() {
		std::unique_lock<std::mutex> lck(lock);
		return count;
	}

	template<class R, class C, class... DArgs, class P, class... Args>
	void Start(R(C::* f)(DArgs...), P&& p, Args&& ... args) {
		std::function<R(void)> fn = [&, f]() { return (*p.*f)(args...); };
		int num = count;
		for (int i = 0; i < num; ++i) {
			std::thread* td = new std::thread([&, fn]() {
				await();
				fn();
			});
			threads.push_back(td);
			this->countDown();
		}
		for (std::thread *t : threads) {
			t->join();
		}
	}

	
private:

	std::vector<std::thread*> threads;
	std::condition_variable cv;
	std::mutex lock;
	int count;

};

} // end namespace codespot

#endif // !CODESPOT_UTILS_COUNTDOWNLATCH_H_