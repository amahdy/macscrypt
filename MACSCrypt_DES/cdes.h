/*###################################
  # DES [Data Encryption Standard]
  # By: Amahdy [www.amahdy.com]
  ###################################*/

#ifndef DESALGORITHM
#define DESALGORITHM

#include "Crypt.h"
#include "bits.h"

/**
 * ==============================================
 * @name DES CLASS
 * @desc Class definition for the DES algorithm.
 * @data %1 bits**: The expanded key.
 *       %2 static const unsigned char[8][4][16]: the S-BOX.
 *       %3 static const unsigned char[64]: the initial permutation 1.
 *       %4 static const unsigned char[48]: the expansion permutation.
 *       %5 static const unsigned char[32]: the permutation after s-box.
 *       %6 static const unsigned char[64]: the final permutation.
 *       %7 static const unsigned char[56]: the permutation choice 1.
 *       %8 static const unsigned char[48]: the permutation choice 2.
 *       %9 unsigned char: number of rounds.
 * @member %1 void*: the main function.
 *         %2 void: rotation (shifting) of the first half.
 *         %3 void: rotation (shifting) of the second half.
 * @public %1 void: constructor, feed it with the number of rounds (default is 16).
 *         %2 void: destructor, never mind ... called automatically.
 *         %3 void: key generator, should call this before anything to generate keys.
 *         %4 void*: call this to encrypt.
 *         %5 void*: call this to decrypt.
 * ==============================================
 */
class CDES: public Crypt {
    bits** keyEx;
    static const unsigned char S_BOX[8][4][16];
    static const unsigned char IP_1[64];
    static const unsigned char EX_P[48];
    static const unsigned char PASB[32];
    static const unsigned char FI_P[64];
    static const unsigned char PC_1[56];
    static const unsigned char PC_2[48];
    unsigned char numberOfRounds;

    void* DES(const void*, bool=false);
    void rotation1(bits*, const unsigned char);
    void rotation2(bits*, const unsigned char);
public:
    CDES(const unsigned char=16);
    ~CDES();
    void KeyGen(const void*);
    void* Encrypt(const void*);
    void* Decrypt(const void*);
};

#endif
