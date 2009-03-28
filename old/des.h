/*###################################
  # DES [Data Encryption Standard]
  # By: Amahdy [www.amahdy.com]
  ###################################*/

#ifndef DESALGORITHM
#define DESALGORITHM

/**
 * ==============================================
 * @name DES CLASS
 * @desc Class definition for the DES algorithm.
 * @data %1 char**: The expanded key.
 *       %2 char[8][4][16]: the S-BOX.
 *       %3 int: number of rounds.
 * @member %1 char*: the main function.
 *         %2 void: hex to bin converter.
 *         %3 void: bin to hex converter.
 *         %4 void: dec to bin converter.
 *         %5 void: bin to dec converter.
 *         %6 void: rotation (shifting).
 *         %7 void: xor funciton.
 * @public %1 void: constructor, feed it with the number of rounds.
 *         %2 void: destructor, never mind ... called automatically.
 *         %3 void: key generator, should call this before anything to generate keys.
 *         %4 char*: call this to encrypt.
 *         %5 char*: call this to decrypt.
 * ==============================================
 */
class CDES:public Crypt {
    char **keyEx;
    char s[8][4][16];
    int numberOfRounds;
    char* DES(char*, bool=false);

    //void HexToBin(const char*, char*);
    //void BinToHex(const char*, char*);
    void DecToBin(const char*, char*);
    void BinToDec(const char*, char*);
    void rotation(char*, int);
    void exor(char*, char*, char*, int);
public:
    CDES(int=16);
    ~CDES();
    void KeyGen(const char*);
    char* Encrypt(char*);
    char* Decrypt(char*);

/**
 * >sample encryption:
 *      CDES DES(NUMBER_OF_ROUNDS);
 *      DES.KeyGen(16HEX_KEY);
 *      OUTPUT=DES.Encrypt(PLAINTEXT);
 *
 * >sample decryption:
 *      CDES DES(NUMBER_OF_ROUNDS);
 *      DES.KeyGen(16HEX_KEY);
 *      OUTPUT=DES.Decrypt(CYPHERTEXT);
 */

};

#endif
