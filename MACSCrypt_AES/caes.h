/* 
 * File:   caes.h
 * Author: Paula
 *
 * Created on March 12, 2009, 4:11 PM
 */

#ifndef _CAES_H
#define	_CAES_H

#include "gf_2.h"
#include "Crypt.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//			AES Cipher (Advanced Encryption Standard)
//	Done by : Paula Mansour Fouad
//	Date	: 21-01-2008
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


class CAES : public Crypt {
private:

    static const unsigned char S_BOX[16 * 16];
    static const unsigned char InvS_BOX[16 * 16];
                                        /*	Key	  |	plainTxt  |	Rounds | RoundKey | ExpandedKey */
    GF_2_ number;                       /*------------------------------------------------------*/
    unsigned char *key                  /*	16	  |		16	  |	  10   |	16	  |		176	    */
    , *states                           /*	24	  |		16	  |	  12   |	16	  |		208	    */
    , *temp                             /*	32	  |		16	  |	  14   |	16	  |		240	    */
    , *expandedKey;                     /*------------------------------------------------------*/
    int KeySize, numberOfRounds, ExpandedKeySize;
    unsigned char *set_S_BOX();
    unsigned char *set_InvS_BOX();
    /**
     * AddRoundKey
     * - a simple bitwise Xor between 16 byte of the state with
     * 16 byte of expanded key.
     */
    void AddRoundKey(int roundNumber);
    /**
     * SubStitudeBytes :
     * - use the S-BOX to perform a Byte-by-Byte substituation.
     */
    void SubStitudeBytes();
    /**
     * InvSubStitudeBytes :
     * - use the InvS-BOX to perform a Byte-by-Byte substituation.
     */
    void InvSubStitudeBytes();
    /**
     * ShiftRowsTransformation :
     * - the first Row has no shift
     * the second Row has circular Right shift by '1' byte
     * the second Row has circular Right shift by '2' byte
     * the second Row has circular Right shift by '3' byte.
     */
    void ShiftRowsTransformation();
    /**
     * InvShiftRowsTransformation :
     * - the first Row has no shift
     * the second Row has circular Left shift by '1' byte
     * the second Row has circular Left shift by '2' byte
     * the second Row has circular Left shift by '3' byte.
     */
    void InvShiftRowsTransformation();
    /**
     * MixColumnsTransformation :
     * - each byte of the column is mapped to a new byte that
     * is a function of the all 4 bytes of the column.
     */
    void MixColumnsTransformation();
    /**
     * InvMixColumnsTransformation :
     * - each byte of the column is mapped to a new byte that
     * is a function of the all 4 bytes of the column.
     */
    void InvMixColumnsTransformation();
    /**
     * RotWord :
     * - perform a 1-byte circular left shifft.
     */
    unsigned char* RotWord(unsigned char temp[4]);
    /**
     * SubWord :
     * - perform a byte substituation on each byte.
     */
    unsigned char* SubWord(unsigned char temp[4]);
    /**
     * RCons
     * - return the round constant
     */
    unsigned char RCons(int i);
public:
    CAES(int NumberOfRounds = 10);
    ~CAES();
    void KeyGen(const char* KEY);
    char* Encrypt(char* plainText);
    char* Decrypt(char *cipherText);
};

#endif	/* _CAES_H */

