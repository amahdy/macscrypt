/*###################################
  # DES [Data Encryption Standard]
  # By: Amahdy [www.amahdy.com]
  ###################################*/

#include "cdes.h"

/**
 * ==============================================
 * @name ROTATION1 / SHIFT1
 * @desc rotate 'data' upon the 'rotNum', (one or two left shifts).
 * @param %1 bits*: the data to be shifted.
 *        %2 const unsigned char: the number of rotation to specify the number of shifts.
 * @return void
 * ==============================================
 */
void CDES::rotation1(bits* data, const unsigned char rotNum) {
    unsigned char* ch = (unsigned char*) data;
    bits aux;
    aux.b0 = data[0].b0;

    ch[0] << 1;
    data[0].b7 = data[1].b0;

    ch[1] << 1;
    data[1].b7 = data[2].b0;

    ch[2] << 1;
    data[2].b7 = data[3].b0;

    data[3].b0 = data[3].b1;
    data[3].b1 = data[3].b2;
    data[3].b2 = data[3].b3;
    data[3].b3 = aux.b0;

    if ((rotNum != 1) && (rotNum != 2) && (rotNum != 9) && (rotNum != 16)) {
        rotation1(data, 1);
    }
}

/**
 * ==============================================
 * @name ROTATION2 / SHIFT2
 * @desc rotate 'data' upon the 'rotNum', (one or two left shifts).
 * @param %1 bits*: the data to be shifted.
 *        %2 const unsigned char: the number of rotation to specify the number of shifts.
 * @return void
 * ==============================================
 */
void CDES::rotation2(bits* data, const unsigned char rotNum) {
    unsigned char* ch = (unsigned char*) data;
    bits aux;
    aux.b0 = data[3].b4;

    data[3].b4 = data[3].b5;
    data[3].b5 = data[3].b6;
    data[3].b6 = data[3].b7;
    data[3].b7 = data[4].b0;

    ch[4] << 1;
    data[4].b7 = data[5].b0;

    ch[5] << 1;
    data[5].b7 = data[6].b0;

    ch[6] << 1;
    data[6].b7 = aux.b0;

    if ((rotNum != 1) && (rotNum != 2) && (rotNum != 9) && (rotNum != 16)) {
        rotation2(data, 1);
    }
}

/**
 * ==============================================
 * @name DES THE MAIN FUNCTION
 * @desc the main function.
 * @param %1 const unsigned char*: 8 decimals representing the INPUT.
 *        %2 bool: false for ENCRYPT and true for DECRYPT.
 * @return unsigned char*: 8 decimals representing the OUTPUT.
 * ==============================================
 */
void* CDES::DES(const void* inputDec_8, bool method) {
    /**
     * Transform the input as an 8 BYTES of type bits.
     */
    bits* input = (bits*) inputDec_8;

    /**
     * IP-1,
     *      left  side: InputAfterIP+0  to InputAfterIP+31.
     *      right side: InputAfterIP+32 to InputAfterIP+63.
     */
    bits* InputAfterIP = new bits[8];
    for (unsigned char i = 0; i < 64; i++) {
        bits::xBit(InputAfterIP, i, input, IP_1[i]);
    }
    
    /**
     * Process of the algorithm numberOfRounds.
     */
    for (unsigned char z = 0; z < numberOfRounds; z++) {
        /**
         * Expansion permutation.
         */
        bits* InputAfterExP = new bits[6];
        for (unsigned char i = 0; i < 48; i++) {
            bits::xBit(InputAfterExP, i, InputAfterIP+32, EX_P[i]);
        }

        /**
         * Decide here which key will be used,
         *      method  >>> DECRYPTION
         *      !method >>> ENCRYPTION
         */
        unsigned char myKey = method ? (numberOfRounds - 1) - z : z;

        /**
         * XOR with key.
         */
        bits* InputAfterKeyXor = new bits[6];
        for (unsigned char i = 0; i < 6; i++) {
            InputAfterKeyXor[i] = InputAfterExP[i] ^ keyEx[myKey][i];
        }
        delete[] InputAfterExP;

        /**
         * Proceed to S-Boxes.
         */
        bits* InputAfterSBox = new bits[4];
        for (unsigned char j = 0; j < 48; j += 6) {
            unsigned char k = j / 6;
            unsigned char sSel = S_BOX[k]
                                      [ (2 * bits::getBit(InputAfterKeyXor, j))
                                      +      bits::getBit(InputAfterKeyXor, j + 5)]
                                      [ (8 * bits::getBit(InputAfterKeyXor, j + 1))
                                      + (4 * bits::getBit(InputAfterKeyXor, j + 2))
                                      + (2 * bits::getBit(InputAfterKeyXor, j + 3))
                                      +      bits::getBit(InputAfterKeyXor, j + 4)];
            for (unsigned char i = 4; i > 0; sSel /= 2) {
                bits::setBit(InputAfterSBox, --i + (4 * k), sSel % 2);
            }
        }
        delete[] InputAfterKeyXor;

        /**
         * Permutation (after s-box).
         */
        bits* InputAfterPSB = new bits[4];
        for (unsigned char i = 0; i < 32; i++) {
            bits::xBit(InputAfterPSB, i, InputAfterSBox, PASB[i]);
        }
        delete[] InputAfterSBox;

        /**
         * XOR final, with the original input left side.
         */
        bits* InputAfterFinalXor = new bits[4];
        for (unsigned char i = 0; i < 4; i++) {
            InputAfterFinalXor[i] = InputAfterIP[i] ^ InputAfterPSB[i];
        }
        delete[] InputAfterPSB;

        /**
         * Re-Initializing for new round.
         */
        for (unsigned char k = 0; k < 32; k++) {
            bits::xBit(InputAfterIP, k, InputAfterIP, k + 32);
            bits::xBit(InputAfterIP, k + 32, InputAfterFinalXor, k);
        }
        delete[] InputAfterFinalXor;
    }

    /**
     * Final permutation FP, inverse of initial pemutation before ending.
     */
    bits* InputFinal = new bits[8];
    for (unsigned char x = 0; x < 32; x++) {
        bits::xBit(InputFinal, x, InputAfterIP, x + 32);
        bits::xBit(InputFinal, x + 32, InputAfterIP, x);
    }
    delete[] InputAfterIP;

    /**
     * Final permutation.
     */
    bits* output = new bits[8];
    for (unsigned char i = 0; i < 64; i++) {
        bits::xBit(output, i, InputFinal, FI_P[i]);
    }
    delete[] InputFinal;

    return output;
}

/**
 * ==============================================
 * @name KEY GENERATOR
 * @desc store in the 'keyEx' the expanded key.
 * @param const unsigned char*: the encryption/decryption process key.
 * @return void
 * ==============================================
 */
void CDES::KeyGen(const void* Key_8) {
    /**
     * Transform the 8 BYTES key to type bits.
     */
    bits* key = (bits*) Key_8;

    /**
     * Permutation choice 1.
     */
    bits* KeyAfterPC1 = new bits[7];
    for(unsigned char i = 0; i < 56; i++) {
        bits::xBit(KeyAfterPC1,  i, key, PC_1[i]);
    }

    /**
     * Completing All Key-Gen numberOfRounds,
     *      left  side: KeyAfterPC1    to KeyAfterPC1+27.
     *      right side: KeyAfterPC1+28 to KeyAfterPC1+55.
     */
    keyEx = new bits*[numberOfRounds];
    for (unsigned char i = 0; i < numberOfRounds; i++) {
        keyEx[i] = new bits[6];
        rotation1(KeyAfterPC1, i + 1);
        rotation2(KeyAfterPC1, i + 1);
        for(unsigned char j = 0; j < 48; j++) {
            bits::xBit(keyEx[i],  0, KeyAfterPC1, PC_2[j]);
        }
    }
    delete[] KeyAfterPC1;

    return;
}

/**
 * ==============================================
 * @name ENCRYPT Function
 * @desc return a DES encrypted version of 'plainText'.
 * @param const unsigned char*: a plain text.
 * @return unsigned char*: a DES cypher text.
 * ==============================================
 */
void* CDES::Encrypt(const void* plainText) {
    return (DES(plainText));
}

/**
 * ==============================================
 * @name DECRYPT Function
 * @desc return a DES decrypted version of 'cipherText'.
 * @param const unsigned char*: a DES cipher text.
 * @return unsigned char*: a plain text.
 * ==============================================
 */
void* CDES::Decrypt(const void* cipherText) {
    return (DES(cipherText, true));
}

/**
 * ==============================================
 * @name CONSTRUCTOR
 * @desc Initialize number of rounds.
 * @param int: Number of rounds [default: 16].
 * @return void
 * ==============================================
 */
CDES::CDES(const unsigned char NumberOfRounds) {
    numberOfRounds = NumberOfRounds;
    return;
}

/**
 * ==============================================
 * @name DESTRUCTOR
 * @desc Destroy the Key Expansion.
 * @param void
 * @return void
 * ==============================================
 */
CDES::~CDES() {
    for (int i = 0; i < numberOfRounds; i++) {
        delete[] keyEx[i];
    }
    delete[] keyEx;
    return;
}

/**
 * DES DATA:
 */
const unsigned char CDES::IP_1[64] = {
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7,
    56, 48, 40, 32, 24, 16,  8,  0,
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6
};

const unsigned char CDES::EX_P[48] = {
    31,  0,  1,  2,  3,  4,
     3,  4,  5,  6,  7,  8,
     7,  8,  9, 10, 11, 12,
    11, 12, 13, 14, 15, 16,
    15, 16, 17, 18, 19, 20,
    19, 20, 21, 22, 23, 24,
    23, 24, 25, 26, 27, 28,
    27, 28, 29, 30, 31,  0
};

const unsigned char CDES::PASB[32] = {
    15,  6, 19, 20,
    28, 11, 27, 16,
     0, 14, 22, 25,
     4, 17, 30,  9,
     1,  7, 23, 13,
    31, 26,  2,  8,
    18, 12, 29,  5,
    21, 10,  3, 24
};

const unsigned char CDES::FI_P[64] = {
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25,
    32,  0, 40,  8, 48, 16, 56, 24
};

const unsigned char CDES::PC_1[56] = {
    56, 48, 40, 32, 24, 16,  8,
     0, 57, 49, 41, 33, 25, 17,
     9,  1, 58, 50, 42, 34, 26,
    18, 10,  2, 59, 51, 43, 35,
    62, 54, 46, 38, 30, 22, 14,
     6, 61, 53, 45, 37, 29, 21,
    13,  5, 60, 52, 44, 36, 28,
    20, 12,  4, 27, 19, 11,  3
};

const unsigned char CDES::PC_2[48] = {
    13, 16, 10, 23,  0,  4,
     2, 27, 14,  5, 20,  9,
    22, 18, 11,  3, 25,  7,
    15,  6, 26, 19, 12,  1,
    40, 51, 30, 36, 46, 54,
    29, 39, 50, 44, 32, 47,
    43, 48, 38, 55, 33, 52,
    45, 41, 49, 35, 28, 31
};

const unsigned char CDES::S_BOX[8][4][16] = {
    {
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
    }, {
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
    }, {
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
    }, {
        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
    }, {
        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
    }, {
        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
    }, {
        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
    }, {
        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9, 10,  3,  5,  6, 11}
    }
};
