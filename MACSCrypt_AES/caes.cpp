//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	Done by : Paula Mansour Fouad
//	Date	: 21-01-2008
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "caes.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//			AES Cipher (Advanced Encryption Standard)
//	Done by : Paula Mansour Fouad
//	Date	: 21-01-2008
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void CAES::AddRoundKey(int roundNumber) {

    for (int i = 0; i < 16; i++)
        *(states + i) = *(states + i) ^ *(expandedKey + i + roundNumber * 16);
}
// SubStitudeBytes :
//	- use the S-BOX to perform a Byte-by-Byte substituation.

void CAES::SubStitudeBytes() {
    for (int x = 0; x < 16; x++)
        *(states + x) = S_BOX[*(states + x)];
}
// InvSubStitudeBytes :
//	- use the InvS-BOX to perform a Byte-by-Byte substituation.

void CAES::InvSubStitudeBytes() {
    for (int x = 0; x < 16; x++)
        *(states + x) = InvS_BOX[*(states + x)];
}
// ShiftRowsTransformation :
//	- the first Row has no shift
//	  the second Row has circular Right shift by '1' byte
//	  the second Row has circular Right shift by '2' byte
//	  the second Row has circular Right shift by '3' byte.

void CAES::ShiftRowsTransformation() {
    int i;
    for (i = 0; i < 16; i++) // populate the temp
        *(temp + i) = *(states + i);
    // we have 4 rows it's counter is n
    for (int n = 0; n < 4; n++) {
        for (i = 4 * n; i < 3 * n + 4; i++) //// begain from 'row number' = 4*n  to 4n-n+4=3*n+4
            *(states + i) = *(temp + i + n); // shift with n-Byte to right
        for (; i < 4 * n + 4; i++) ///// the rest Bytes of the row from i to 4n+4
            *(states + i) = *(temp + i + n - 4); // copy from left to right "Right shift"
    }
}
// InvShiftRowsTransformation :
//	- the first Row has no shift
//	  the second Row has circular Left shift by '1' byte
//	  the second Row has circular Left shift by '2' byte
//	  the second Row has circular Left shift by '3' byte.

void CAES::InvShiftRowsTransformation() {
    int i;
    for (i = 0; i < 16; i++) // pobulate the temp
        *(temp + i) = *(states + i);
    // we have 4 rows it's counter is n
    for (int n = 0; n < 4; n++) {
        for (i = 4 * n; i < 3 * n + 4; i++) //// begain from 'row number' = 4*n  to 'row number' = 4n-n+4=3*n+4
            *(states + i + n) = *(temp + i); // shift with n-Byte to left
        for (; i < 4 * n + 4; i++) ///// the rest Bytes of the row from i to 4n+4
            *(states + i + n - 4) = *(temp + i); // copy from right to left "Left shift"
    }
}
//	MixColumnsTransformation :
//	- each byte of the column is mapped to a new byte that
//	  is a function of the all 4 bytes of the column.

void CAES::MixColumnsTransformation() {
    int i;
    for (i = 0; i < 16; i++) // pobulate the temp
        *(temp + i) = *(states + i);
    for (int j = 0; j < 4; j++) {
        // i ==> the row number		0<=i<4
        // j==> the column number	0<=j<4
        // f(i,j) = 4+i + j
        *(states + j) = number.MultiplyBy2GF2(*(temp + j)) ^ number.MultiplyBy3GF2(*(temp + 4 + j)) ^ *(temp + 8 + j) ^ *(temp + 12 + j);
        *(states + 4 + j) = *(temp + j) ^ number.MultiplyBy2GF2(*(temp + 4 + j)) ^ number.MultiplyBy3GF2(*(temp + 8 + j)) ^ *(temp + 12 + j);
        *(states + 8 + j) = *(temp + j) ^ *(temp + 4 + j) ^ number.MultiplyBy2GF2(*(temp + 8 + j)) ^ number.MultiplyBy3GF2(*(temp + 12 + j));
        *(states + 12 + j) = number.MultiplyBy3GF2(*(temp + j)) ^ *(temp + 4 + j) ^ *(temp + 8 + j) ^ number.MultiplyBy2GF2(*(temp + 12 + j));
    }
}
//	InvMixColumnsTransformation :
//	- each byte of the column is mapped to a new byte that
//	  is a function of the all 4 bytes of the column.

void CAES::InvMixColumnsTransformation() {
    int i;
    for (i = 0; i < 16; i++) // pobulate the temp
        *(temp + i) = *(states + i);
    for (int j = 0; j < 4; j++) {
        // i ==> the row number		0<=i<4
        // j==> the column number	0<=j<4
        // f(i,j) = 4+i + j
        *(states + j) = number.MultiplyGF2(*(temp + j), 0x0e) ^ number.MultiplyGF2(*(temp + 4 + j), 0x0b) ^ number.MultiplyGF2(*(temp + 8 + j), 0x0d) ^ number.MultiplyGF2(*(temp + 12 + j), 0x09);
        *(states + 4 + j) = number.MultiplyGF2(*(temp + j), 0x09) ^ number.MultiplyGF2(*(temp + 4 + j), 0x0e) ^ number.MultiplyGF2(*(temp + 8 + j), 0x0b) ^ number.MultiplyGF2(*(temp + 12 + j), 0x0d);
        *(states + 8 + j) = number.MultiplyGF2(*(temp + j), 0x0d) ^ number.MultiplyGF2(*(temp + 4 + j), 0x09) ^ number.MultiplyGF2(*(temp + 8 + j), 0x0e) ^ number.MultiplyGF2(*(temp + 12 + j), 0x0b);
        *(states + 12 + j) = number.MultiplyGF2(*(temp + j), 0x0b) ^ number.MultiplyGF2(*(temp + 4 + j), 0x0d) ^ number.MultiplyGF2(*(temp + 8 + j), 0x09) ^ number.MultiplyGF2(*(temp + 12 + j), 0x0e);
    }
}
// RotWord :
//	- perform a 1-byte circular left shifft.

unsigned char* CAES::RotWord(unsigned char temp[4]) {
    unsigned char buffer = temp[0];
    for (int i = 0; i < 3; i++)
        temp[i] = temp[i + 1];
    temp[3] = buffer;
    return temp;
}
// SubWord :
//	- perform a byte substituation on each byte.

unsigned char* CAES::SubWord(unsigned char temp[4]) {
    for (int i = 0; i < 4; i++)
        temp[i] = S_BOX[temp[i]];
    return temp;
}
// RCons
// - return the round constant

unsigned char CAES::RCons(int i) {
    /*
    int RC(int j)
    {
            if(j==1)
                    return 1;
            else
                    return number.MultiplyBy2GF2(RC(j-1));
    }
     */
    switch (i) {
        case 1: return 0x01;
            break;
        case 2: return 0x02;
            break;
        case 3: return 0x04;
            break;
        case 4: return 0x08;
            break;
        case 5: return 0x10;
            break;
        case 6: return 0x20;
            break;
        case 7: return 0x40;
            break;
        case 8: return 0x80;
            break;
        case 9: return 0x1b;
            break;
        case 10: return 0x36;
            break;
        case 11: return 0x6c;
            break;
        case 12: return 0xd8;
            break;
        case 13: return 0xab;
            break;
        case 14: return 0x4d;
            break;
    }
    return 0x00;
}

CAES::CAES(int NumberOfRounds) {
//    InvS_BOX = set_InvS_BOX();
    numberOfRounds = (NumberOfRounds >= 10) ? NumberOfRounds : 10;
    KeySize = (numberOfRounds - 10)*4 + 16;
    ExpandedKeySize = (numberOfRounds + 1)*16;

    key = new unsigned char[KeySize];
    states = new unsigned char[17];
    temp = new unsigned char[17];
    expandedKey = new unsigned char[ExpandedKeySize];

    states[16] = '\0';
    temp[16] = '\0';

    for (int i = 0; i < 16; i++)
        *(key + i) = *(states + i) = *(temp + i) = 0x00;

    for (int i = 0; i < 176; i++)
        *(expandedKey + i) = 0x00;
}

CAES::~CAES() {
    delete[] key;
    delete[] temp;
    delete[] expandedKey;
    delete[] states;
}

char* CAES::Encrypt(char* plainText) {
    unsigned char* pt = (unsigned char*) plainText;
    for (int x = 0; x < 16; x++)
        *(states + x) = *(pt + x);
    int Round = 0;
    AddRoundKey(Round);
    for (Round = 1; Round < numberOfRounds; Round++) {
        SubStitudeBytes();
        ShiftRowsTransformation();
        MixColumnsTransformation();
        AddRoundKey(Round);
    }
    SubStitudeBytes();
    ShiftRowsTransformation();
    AddRoundKey(Round);

    return (char*) states;
}

char* CAES::Decrypt(char *cipherText) {
    unsigned char* ct = (unsigned char*) cipherText;
    for (int x = 0; x < 16; x++)
        *(states + x) = *(ct + x);
    int Round = 0;
    AddRoundKey(numberOfRounds - Round);
    for (Round = 1; Round < numberOfRounds; Round++) {
        InvShiftRowsTransformation();
        InvSubStitudeBytes();
        AddRoundKey(numberOfRounds - Round);
        InvMixColumnsTransformation();
    }
    InvShiftRowsTransformation();
    InvSubStitudeBytes();
    AddRoundKey(numberOfRounds - Round);

    return (char*) states;
}

void CAES::KeyGen(const char* KEY) {

    for (int i = 0; i < 16; i++)
        *(key + i) = (unsigned char) *(KEY + i);

    for (int i = 0; i < 16; i++)
        *(expandedKey + i) = *(key + i);
    unsigned char* buffer = new unsigned char[4];
    for (int i = 0; i < 4; i++)
        *(buffer + i) = 0x00;

    for (int i = 16; i < ExpandedKeySize; i = i + 4) {
        for (int x = 0; x < 4; x++)
            *(buffer + x) = *(expandedKey + x + i - 4);
        if (i % 16 == 0) {
            buffer = RotWord(buffer);
            buffer = SubWord(buffer);
            *buffer = *buffer ^ RCons(i / 16);
        }
        for (int x = 0; x < 4; x++)
            *(expandedKey + i + x) = *(buffer + x)^*(expandedKey + i - 16 + x);
    }
    delete[] buffer;
}

const unsigned char CAES::S_BOX [16 * 16] = {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76
    , 0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0
    , 0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15
    , 0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75
    , 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84
    , 0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF
    , 0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8
    , 0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2
    , 0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73
    , 0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB
    , 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79
    , 0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08
    , 0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A
    , 0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E
    , 0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF
    , 0x8C, 0xA1, 0x89, 0x0d, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};

const unsigned char CAES::InvS_BOX [16 * 16] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB
    , 0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB
    , 0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E
    , 0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25
    , 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92
    , 0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84
    , 0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06
    , 0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B
    , 0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73
    , 0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E
    , 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B
    , 0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4
    , 0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F
    , 0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF
    , 0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61
    , 0X17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};
