/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-11
==============================================================================*/

#include <cryptopp/rsa.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>

#include "codespot/tools/cryptography.h"


namespace codespot {

using namespace CryptoPP;

void ExportKeys(std::string& priFile, std::string& pubFile) {
	AutoSeededRandomPool rnd;
	InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rnd, 3072);
	RSA::PrivateKey privateKey(params);
	RSA::PublicKey publicKey(params);
	privateKey.Save(FileSink(priFile.data()).Ref());
	publicKey.Save(FileSink(pubFile.data()).Ref());
}

std::string Encrypt(std::string& data, std::string& keyPath) {
	std::string cipher, encoded;
	AutoSeededRandomPool rng;
	RSA::PublicKey publicKey;
	publicKey.Load(FileSource(keyPath.data(), true, NULL, true).Ref());
	RSAES_OAEP_SHA_Encryptor Encryptor(publicKey);
	StringSource ss1(data, true,
		new PK_EncryptorFilter(rng, Encryptor,
			new StringSink(cipher)
		) 
	); 
	std::string ;
	StringSource ss(cipher, true,
		new HexEncoder(
			new StringSink(encoded)
		)
	);
	return encoded;
}

std::string Decrypt(std::string& encoded, std::string& keyPath) {
	std::string recovered, cipher;
	AutoSeededRandomPool rng;
	RSA::PrivateKey privateKey;
	privateKey.Load(FileSource(keyPath.data(), true, NULL, true).Ref());

	StringSource ss(encoded, true,
		new HexDecoder(
			new StringSink(cipher)
		)
	);

	RSAES_OAEP_SHA_Decryptor Decryptor(privateKey);
	StringSource ss2(cipher, true,
		new PK_DecryptorFilter(rng, Decryptor,
			new StringSink(recovered)
		)
	);
    
	return recovered;
}

std::string AESEncrypt(std::string& plain, std::string& skey) {
	std::string result;
	byte* hkey = (byte*)skey.data();
	SecByteBlock key(hkey, AES::MAX_KEYLENGTH), iv(hkey, AES::BLOCKSIZE);
	CFB_Mode<AES>::Encryption Encryptor(key, key.size(), iv, 1);
	StringSource(plain, true, 
		new StreamTransformationFilter(Encryptor, 
			new HexEncoder(
				new StringSink(result))));
	return result;
}

std::string AESDecrypt(std::string& encoded, std::string& skey) {
	std::string result, cipher;
	byte* hkey = (byte*)skey.data();
	SecByteBlock key(hkey, AES::MAX_KEYLENGTH), iv(hkey, AES::BLOCKSIZE);
	CFB_Mode<AES>::Decryption Decryptor(key, key.size(), iv, 1);
	StringSource ss(encoded, true,
		new HexDecoder(
			new StringSink(cipher)
		) 
	); 
	StringSource(cipher, true,
		new StreamTransformationFilter(Decryptor, 
			new StringSink(result)
		)
	);
	return result;
}

std::string SHA_256(std::string& data) {
	std::string digest;
	SHA256 hash;
	StringSource foo(data, true, 
		new HashFilter(hash, 
			new HexEncoder(
				new StringSink(digest))));
	return digest;
}

std::string Str2Hex(const std::string& input) {
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();
	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i) {
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}

} // end namespace codespot