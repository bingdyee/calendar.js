/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

Eigen/grpc/Crypto++

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-11
==============================================================================*/

#include <iostream>
#include <thread>

#include "codespot/utils/cryptography.h"
#include "codespot/utils/logger.h"
#include "codespot/utils/time_util.h"
#include "codespot/utils/snowflake.h"
#include "codespot/utils/countdownlatch.h"

using namespace std;
using namespace codespot;

class B {

public:
	void hello(std::string& m) {
		std::cout << m << std::endl;
	}


};


int main(int args, char** argv) {
	
	Countdownlatch latch(6);
	B b;
	std::string a = "Hello";
	latch.Start(&B::hello, &b, a);

	system("pause");
	return 0;
}