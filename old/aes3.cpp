#include "stdafx.h"

CAES3::CAES3(int NumberOfRounds)
{
	AES1=new CAES(NumberOfRounds);
	AES2=new CAES(NumberOfRounds);
}
CAES3::~CAES3()
{
	delete AES1,AES2;
}
char* CAES3::Encrypt(char* plainText)
{	
	return AES1->Encrypt(AES2->Decrypt(AES1->Encrypt(plainText)));
}
char* CAES3::Decrypt(char *cipherText)
{			
	return AES1->Decrypt(AES2->Encrypt(AES1->Decrypt(cipherText)));
}
void CAES3::KeyGen(const char* KEY)
{
	AES1->KeyGen(KEY);
	AES2->KeyGen(KEY+16);
}