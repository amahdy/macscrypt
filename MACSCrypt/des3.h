# ifndef DES3ALGORITHM
# define DES3ALGORITHM

#include "DES.h"

class CDES3:public Crypt
{
	CDES *DES1,*DES2;
	char* key;
public:
	CDES3(int NumberOfRounds=16);
	~CDES3();
	void KeyGen(const char*);
	char* Encrypt(char*);
	char* Decrypt(char*);
};
# endif