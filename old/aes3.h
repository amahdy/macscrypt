# ifndef AES3ALGORITHM
# define AES3ALGORITHM

#include "AES.h"

class CAES3:public Crypt
{
	CAES *AES1,*AES2;
	char* key;
public:
	CAES3(int NumberOfRounds=10);
	~CAES3();
	void KeyGen(const char*);
	char* Encrypt(char*);
	char* Decrypt(char*);
};
# endif