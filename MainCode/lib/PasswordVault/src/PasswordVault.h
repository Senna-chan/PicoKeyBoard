// PasswordVault.h

#ifndef _PASSWORDVAULT_h
#define _PASSWORDVAULT_h

#include <Arduino.h>
#include <Crypto.h>
#include <AES.h>

class PasswordVaultClass {
private:
	AES128 hash;

public:
	enum CryptResult {
		OK,
		KEY_TOO_LONG,
		KEY_NOT_ACCEPTED,
		INPUTSIZE_INCORRECT,
		OUTPUTSIZE_INCORRECT
	};
	CryptResult encryptPassword(uint8_t* input, uint8_t inputSize, uint8_t* output, uint8_t outputSize, uint8_t* key, uint8_t keySize);
	CryptResult decryptPassword(uint8_t* input, uint8_t inputSize, uint8_t* output, uint8_t outputSize, uint8_t* key, uint8_t keySize);
};

extern PasswordVaultClass PasswordVault;
#endif

