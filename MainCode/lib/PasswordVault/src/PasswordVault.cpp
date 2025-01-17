//
//
//

#include "PasswordVault.h"

PasswordVaultClass::CryptResult PasswordVaultClass::encryptPassword(uint8_t* input, uint8_t inputSize, uint8_t* output, uint8_t outputSize, uint8_t* key, uint8_t keySize)
{
	uint8_t paddedKey[16] = { 0 };
	if (keySize > 16)
	{
		return KEY_TOO_LONG;
	}
	else
	{
		memmove(paddedKey, key, keySize);
	}
	if (!hash.setKey(paddedKey, 16))
	{
		return KEY_NOT_ACCEPTED;
	}
	memset(paddedKey, 0, 16);

	size_t blockSize = hash.blockSize();

	if ((outputSize % blockSize) != 0)
	{
		return OUTPUTSIZE_INCORRECT;
	}

	size_t blockAmounts = inputSize / blockSize;
	size_t modAmount = inputSize % blockSize;
	for (size_t i = 0; i < blockAmounts; i++)
	{
		hash.encryptBlock(output, input);
		output += blockSize;
		input += blockSize;
	}
	if (modAmount)
	{
		uint8_t paddedInput[blockSize] = { 0 };
		memcpy(paddedInput, input, modAmount);
		hash.encryptBlock(output, paddedInput);
	}
	hash.clear();
	return OK;
}

PasswordVaultClass::CryptResult PasswordVaultClass::decryptPassword(uint8_t* input, uint8_t inputSize, uint8_t* output, uint8_t outputSize, uint8_t* key, uint8_t keySize)
{
	uint8_t paddedKey[16] = { 0 };
	if (keySize > 16)
	{
		return KEY_TOO_LONG;
	}
	else
	{
		memmove(paddedKey, key, keySize);
	}
	if (!hash.setKey(paddedKey, 16))
	{
		return KEY_NOT_ACCEPTED;
	}
	memset(paddedKey, 0, 16);

	size_t blockSize = hash.blockSize();

	if ((outputSize % blockSize) != 0)
	{
		return OUTPUTSIZE_INCORRECT;
	}

	size_t blockAmounts = inputSize / blockSize;
	size_t modAmount = inputSize % blockSize;
	for (size_t i = 0; i < blockAmounts; i++)
	{
		hash.decryptBlock(output, input);
		output += blockSize;
		input += blockSize;
	}
	if (modAmount)
	{
		uint8_t paddedInput[blockSize] = { 0 };
		memcpy(paddedInput, input, modAmount);
		hash.decryptBlock(output, paddedInput);
	}
	hash.clear();
	return OK;
}

PasswordVaultClass PasswordVault;
