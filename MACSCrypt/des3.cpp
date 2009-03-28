#include "stdafx.h"

CDES3::CDES3(int NumberOfRounds)
{
	DES1=new CDES(NumberOfRounds);
	DES2=new CDES(NumberOfRounds);
}
CDES3::~CDES3()
{
	delete DES1,DES2;
}
char* CDES3::Encrypt(char* plainText)
{	
	return DES1->Encrypt(DES2->Decrypt(DES1->Encrypt(plainText)));
}
char* CDES3::Decrypt(char *cipherText)
{			
	return DES1->Decrypt(DES2->Encrypt(DES1->Decrypt(cipherText)));
}
void CDES3::KeyGen(const char* KEY)
{
	DES1->KeyGen(KEY);
	DES2->KeyGen(KEY+16);
}