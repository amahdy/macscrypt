#ifndef CRYPT
#define CRYPT

class Crypt
{
public:
	virtual void KeyGen(const char*)=0;
	virtual char* Encrypt(char*)=0;
	virtual char* Decrypt(char*)=0;
};

#endif