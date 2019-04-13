/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

Eigen/grpc/Crypto++

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-11
==============================================================================*/

#include <iostream>
#include <thread>

#include "codespot/tools/cryptography.h"
#include "codespot/tools/logger.h"
#include "codespot/tools/time_util.h"
#include "codespot/tools/snowflake.h"
#include "codespot/tools/countdownlatch.h"

using namespace std;
using namespace codespot;


int main(int args, char** argv) {
	std::string data = "I work for smarter cybersecurity with machine learning.";
	std::string priFile = "D://rsa_key";
	std::string pubFile = "D://rsa_key.pub";
	// ExportKeys(priFile, pubFile);

	std::string cipher = Encrypt(data, pubFile);
	std::cout << "Cipher Text: " << cipher << std::endl;

	std::string recovered = Decrypt(cipher, priFile);
	std::cout << "Recovered Text: " << recovered << std::endl;

	system("pause");
	return 0;
}