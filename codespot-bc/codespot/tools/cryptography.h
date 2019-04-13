/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-11
==============================================================================*/

#ifndef CODESPOT_UTILS_CRYPTOGRAPHY_H_
#define CODESPOT_UTILS_CRYPTOGRAPHY_H_

#include <vector>

namespace codespot {

// Generate public keyand private key
void ExportKeys(std::string&, std::string&);

// Encrypt data with RSA
std::string Encrypt(std::string&, std::string&);

// Decrypt data with RSA
std::string Decrypt(std::string&, std::string&);

// Encrypt data with AES
std::string AESEncrypt(std::string&, std::string&);

// Decrypt data with AES
std::string AESDecrypt(std::string&, std::string&);

// sha-256
std::string SHA_256(std::string&);

// string to hex
std::string Str2Hex(const std::string&);

} // end namespace codespot

#endif // !CODESPOT_UTILS_CRYPTOGRAPHY_H_

