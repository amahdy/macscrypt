/*###################################
 #	By : Amahdy [www.amahdy.com]	#
 ###################################*/

#ifndef DESALGORITHM
#define DESALGORITHM

/*###################################
 #	DES "Data Encryption Standard"	#
 #		====ByAmahdy====			#
 #		[www.amahdy.com]			#
 ###################################*/

class CDES:public Crypt
{
	char **keyEx;									//expanded key
	char s[8][4][16];								//s-boxs
	int numberOfRounds;										//number of rounds to execute the algorithm
	char* DES(char*,bool=false);			//GO from here !

	//additional functions:
	/*
	void HexToBin(const char*, char*);
	void BinToHex(const char*, char*);
	*/
	void DecToBin(const char*, char*);
	void BinToDec(const char*, char*);
	void rotation(char*, int);
	void exor(char*, char*, char*, int);
public:
	CDES(int=16);							//consturctor, feed it with the number of rounds
	~CDES();								//destructor, never mind ... called automatically
	void KeyGen(const char*);						//should call this before anything to generate keys
	char* Encrypt(char*);					//Call this to encrypt
	char* Decrypt(char*);					//Call this to decrypt

/*
	>sample encryption:
	CDES DES(NUMBER_OF_ROUNDS);
	DES.KeyGen(16HEX_KEY);
	OUTPUT=DES.Encrypt(PLAINTEXT);

	>sample decryption:
	CDES DES(NUMBER_OF_ROUNDS);
	DES.KeyGen(16HEX_KEY);
	OUTPUT=DES.Decrypt(CYPHERTEXT);
*/

};
#endif