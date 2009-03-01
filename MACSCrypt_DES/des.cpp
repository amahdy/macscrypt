/*###################################
  # DES [Data Encryption Standard]
  # By: Amahdy [www.amahdy.com]
  ###################################*/

#include "des.h"

/**
 * ==============================================
 * @name HEX16 TO BIN64 CONVERTER
 * @desc convert a string of 16 hexadecimals to a string of 64 bits.
 * @param %1 const char*: the input 16 hexadecimal.
 *        %2 char*: the output 64 binary.
 * @return void [return is specified as param %2].
 * @note NOT USED!
 * ==============================================
 *//*
void CDES::HexToBin(const char *hex, char *bin) {
    for (char k = 0; k < 16; k++) {
        char a = hex[k]-'0';
        if (a > 16)
            a -= 7;
        for (char z = 4; z > 0; a /= 2)
            bin[--z+4*k] = a%2;
    }
}*/

/**
 * ==============================================
 * @name BIN64 TO HEX16 CONVERTER
 * @desc convert a string of 64 bits to a string of 16 hexadecimals.
 * @param %1 const char*: the input 64 binary.
 *        %2 char*: the output 16 hexadecimal.
 * @return void [return is specified as param %2].
 * @note NOT USED!
 * ==============================================
 *//*
void CDES::BinToHex(const char *bin, char *hex) {
    char t[17]="0123456789ABCDEF";
    for (char i = 0; i < 16; i++)
        hex[i] = t[(8*bin[0+i*4])+(4*bin[1+i*4])+(2*bin[2+i*4])+bin[3+i*4]];
}*/

/**
 * ==============================================
 * @name dec_8 TO bin_64 CONVERTER
 * @desc convert a string of 8 char to a string of 64 char (each char is a bit).
 * @param %1 const char*: the input 8 decimal.
 *        %2 char*: the output 64 binary.
 * @return void [return is specified as param %2].
 * ==============================================
 */
void CDES::DecToBin(const char *dec_8, char *bin_64) {
    int number;
    for (int i = 0, z = 0; i < 8; i++) {
        number = dec_8[i] + 128;
        for (z = 0; z < 8; z++, number /= 2)
            bin_64[(i * 8) + 7 - z] = (number % 2) ? 1 : 0;
    }
}

/**
 * ==============================================
 * @name bin_64 TO dec_8 CONVERTER
 * @desc convert a string of 64 char (each char is a bit) to a string of 8 char.
 * @param %1 const char*: the input 64 binary.
 *        %2 char*: the output 8 decimal.
 * @return void [return is specified as param %2].
 * ==============================================
 */
void CDES::BinToDec(const char *bin_64, char *dec_8) {
    for (int i = 0; i < 8; i++)
        dec_8[i] = 128 * bin_64[i * 8] + 64 * bin_64[1 + (i * 8)] + 32 * bin_64[2 + (i * 8)] + 16 * bin_64[3 + (i * 8)] + 8 * bin_64[4 + (i * 8)] + 4 * bin_64[5 + (i * 8)] + 2 * bin_64[6 + (i * 8)] + bin_64[7 + (i * 8)] - 128;
}

/**
 * ==============================================
 * @name ROTATION / SHIFT
 * @desc rotate 'data' upon the 'rotNum', (one or two left shifts).
 * @param %1 char*: the data to be shifted.
 *        %2 int: the number of rotation to specify the number of shifts.
 * @return void
 * ==============================================
 */
void CDES::rotation(char *data, int rotNum) {
    char aux = *data;
    for (int i = 0; i < 27; i++)
        data[i] = data[i + 1];
    data[27] = aux;
    if ((rotNum != 1) && (rotNum != 2) && (rotNum != 9) && (rotNum != 16))
        rotation(data, 1);
}

/**
 * ==============================================
 * @name XOR
 * @desc take 'a' and 'b' both of length 'n', make xor between them and store result in 'result'.
 * @param %1 char*: the xor left hand side.
 *        %2 char*: the xor right hand side.
 *        %3 char*: the returned result.
 *        %4 int: the length of both of %1 and %2.
 * @return void [return is specified as param %3].
 * ==============================================
 */
void CDES::exor(char *a, char *b, char *result, int n) {
    for (int i = 0; i < n; i++)
        result[i] = a[i]^b[i];
}

/**
 * ==============================================
 * @name KEY GENERATOR
 * @desc store in the 'keyEx' the expanded key.
 * @param const char*: the encryption/decryption process key.
 * @return void
 * ==============================================
 */
void CDES::KeyGen(const char *Key_8) {
    char *key = new char[64];
    DecToBin(Key_8, key);

    /**
     * Generation Of Keys.
     */
    
    /*PermutationChoice-1: =====================================================================================================================================================*/
    char *KeyAfterPC1= new char[56];
    KeyAfterPC1[ 0]=key[56]; KeyAfterPC1[ 1]=key[48]; KeyAfterPC1[ 2]=key[40]; KeyAfterPC1[ 3]=key[32]; KeyAfterPC1[ 4]=key[24]; KeyAfterPC1[ 5]=key[16]; KeyAfterPC1[ 6]=key[ 8];
    KeyAfterPC1[ 7]=key[ 0]; KeyAfterPC1[ 8]=key[57]; KeyAfterPC1[ 9]=key[49]; KeyAfterPC1[10]=key[41]; KeyAfterPC1[11]=key[33]; KeyAfterPC1[12]=key[25]; KeyAfterPC1[13]=key[17];
    KeyAfterPC1[14]=key[ 9]; KeyAfterPC1[15]=key[ 1]; KeyAfterPC1[16]=key[58]; KeyAfterPC1[17]=key[50]; KeyAfterPC1[18]=key[42]; KeyAfterPC1[19]=key[34]; KeyAfterPC1[20]=key[26];
    KeyAfterPC1[21]=key[18]; KeyAfterPC1[22]=key[10]; KeyAfterPC1[23]=key[ 2]; KeyAfterPC1[24]=key[59]; KeyAfterPC1[25]=key[51]; KeyAfterPC1[26]=key[43]; KeyAfterPC1[27]=key[35];
    KeyAfterPC1[28]=key[62]; KeyAfterPC1[29]=key[54]; KeyAfterPC1[30]=key[46]; KeyAfterPC1[31]=key[38]; KeyAfterPC1[32]=key[30]; KeyAfterPC1[33]=key[22]; KeyAfterPC1[34]=key[14];
    KeyAfterPC1[35]=key[ 6]; KeyAfterPC1[36]=key[61]; KeyAfterPC1[37]=key[53]; KeyAfterPC1[38]=key[45]; KeyAfterPC1[39]=key[37]; KeyAfterPC1[40]=key[29]; KeyAfterPC1[41]=key[21];
    KeyAfterPC1[42]=key[13]; KeyAfterPC1[43]=key[ 5]; KeyAfterPC1[44]=key[60]; KeyAfterPC1[45]=key[52]; KeyAfterPC1[46]=key[44]; KeyAfterPC1[47]=key[36]; KeyAfterPC1[48]=key[28];
    KeyAfterPC1[49]=key[20]; KeyAfterPC1[50]=key[12]; KeyAfterPC1[51]=key[ 4]; KeyAfterPC1[52]=key[27]; KeyAfterPC1[53]=key[19]; KeyAfterPC1[54]=key[11]; KeyAfterPC1[55]=key[ 3];
    /*==========================================================================================================================================================================*/

    /**
     * Completing All Key-Gen numberOfRounds,
     *      left  side: KeyAfterPC1    to KeyAfterPC1+27.
     *      right side: KeyAfterPC1+28 to KeyAfterPC1+55.
     */
    keyEx = new char*[numberOfRounds];
    for (int i = 0; i < numberOfRounds; i++) {
        keyEx[i] = new char[48];
        rotation(KeyAfterPC1, i + 1);
        rotation(KeyAfterPC1 + 28, i + 1);
        /*PermutationChoice-2: ==========================================================================================================================================================*/
        keyEx[i][ 0]=KeyAfterPC1[13]; keyEx[i][ 1]=KeyAfterPC1[16]; keyEx[i][ 2]=KeyAfterPC1[10]; keyEx[i][ 3]=KeyAfterPC1[23]; keyEx[i][ 4]=KeyAfterPC1[ 0]; keyEx[i][ 5]=KeyAfterPC1[ 4];
        keyEx[i][ 6]=KeyAfterPC1[ 2]; keyEx[i][ 7]=KeyAfterPC1[27]; keyEx[i][ 8]=KeyAfterPC1[14]; keyEx[i][ 9]=KeyAfterPC1[ 5]; keyEx[i][10]=KeyAfterPC1[20]; keyEx[i][11]=KeyAfterPC1[ 9];
        keyEx[i][12]=KeyAfterPC1[22]; keyEx[i][13]=KeyAfterPC1[18]; keyEx[i][14]=KeyAfterPC1[11]; keyEx[i][15]=KeyAfterPC1[ 3]; keyEx[i][16]=KeyAfterPC1[25]; keyEx[i][17]=KeyAfterPC1[ 7];
        keyEx[i][18]=KeyAfterPC1[15]; keyEx[i][19]=KeyAfterPC1[ 6]; keyEx[i][20]=KeyAfterPC1[26]; keyEx[i][21]=KeyAfterPC1[19]; keyEx[i][22]=KeyAfterPC1[12]; keyEx[i][23]=KeyAfterPC1[ 1];
        keyEx[i][24]=KeyAfterPC1[40]; keyEx[i][25]=KeyAfterPC1[51]; keyEx[i][26]=KeyAfterPC1[30]; keyEx[i][27]=KeyAfterPC1[36]; keyEx[i][28]=KeyAfterPC1[46]; keyEx[i][29]=KeyAfterPC1[54];
        keyEx[i][30]=KeyAfterPC1[29]; keyEx[i][31]=KeyAfterPC1[39]; keyEx[i][32]=KeyAfterPC1[50]; keyEx[i][33]=KeyAfterPC1[44]; keyEx[i][34]=KeyAfterPC1[32]; keyEx[i][35]=KeyAfterPC1[47];
        keyEx[i][36]=KeyAfterPC1[43]; keyEx[i][37]=KeyAfterPC1[48]; keyEx[i][38]=KeyAfterPC1[38]; keyEx[i][39]=KeyAfterPC1[55]; keyEx[i][40]=KeyAfterPC1[33]; keyEx[i][41]=KeyAfterPC1[52];
        keyEx[i][42]=KeyAfterPC1[45]; keyEx[i][43]=KeyAfterPC1[41]; keyEx[i][44]=KeyAfterPC1[49]; keyEx[i][45]=KeyAfterPC1[35]; keyEx[i][46]=KeyAfterPC1[28]; keyEx[i][47]=KeyAfterPC1[31];
        /*===============================================================================================================================================================================*/
    }

    //Clean Up:
    delete[] key;
    delete[] KeyAfterPC1;
    return;
}

/**
 * ==============================================
 * @name DES THE MAIN FUNCTION
 * @desc the main function.
 * @param %1 char*: 16 hexadecimals representing the INPUT.
 *        %2 bool: false for ENCRYPT and true for DECRYPT.
 * @return char*: 16 hexadecimals representing the OUTPUT.
 * ==============================================
 */
char* CDES::DES(char *inputDec_8, bool method) {
    char *input = new char[64];
    DecToBin(inputDec_8, input);

    /**
    * IP-1,
    *      left  side: InputAfterIP    to InputAfterIP+31.
    *      right side: InputAfterIP+32 to InputAfterIP+63.
    */
    /*Initial permutation: ======================================================================================================================================================================================================*/
    char *InputAfterIP=new char[64];
    InputAfterIP[ 0]=input[57]; InputAfterIP[ 1]=input[49]; InputAfterIP[ 2]=input[41]; InputAfterIP[ 3]=input[33]; InputAfterIP[ 4]=input[25]; InputAfterIP[ 5]=input[17]; InputAfterIP[ 6]=input[ 9]; InputAfterIP[ 7]=input[ 1];
    InputAfterIP[ 8]=input[59]; InputAfterIP[ 9]=input[51]; InputAfterIP[10]=input[43]; InputAfterIP[11]=input[35]; InputAfterIP[12]=input[27]; InputAfterIP[13]=input[19]; InputAfterIP[14]=input[11]; InputAfterIP[15]=input[ 3];
    InputAfterIP[16]=input[61]; InputAfterIP[17]=input[53]; InputAfterIP[18]=input[45]; InputAfterIP[19]=input[37]; InputAfterIP[20]=input[29]; InputAfterIP[21]=input[21]; InputAfterIP[22]=input[13]; InputAfterIP[23]=input[ 5];
    InputAfterIP[24]=input[63]; InputAfterIP[25]=input[55]; InputAfterIP[26]=input[47]; InputAfterIP[27]=input[39]; InputAfterIP[28]=input[31]; InputAfterIP[29]=input[23]; InputAfterIP[30]=input[15]; InputAfterIP[31]=input[ 7];
    InputAfterIP[32]=input[56]; InputAfterIP[33]=input[48]; InputAfterIP[34]=input[40]; InputAfterIP[35]=input[32]; InputAfterIP[36]=input[24]; InputAfterIP[37]=input[16]; InputAfterIP[38]=input[ 8]; InputAfterIP[39]=input[ 0];
    InputAfterIP[40]=input[58]; InputAfterIP[41]=input[50]; InputAfterIP[42]=input[42]; InputAfterIP[43]=input[34]; InputAfterIP[44]=input[26]; InputAfterIP[45]=input[18]; InputAfterIP[46]=input[10]; InputAfterIP[47]=input[ 2];
    InputAfterIP[48]=input[60]; InputAfterIP[49]=input[52]; InputAfterIP[50]=input[44]; InputAfterIP[51]=input[36]; InputAfterIP[52]=input[28]; InputAfterIP[53]=input[20]; InputAfterIP[54]=input[12]; InputAfterIP[55]=input[ 4];
    InputAfterIP[56]=input[62]; InputAfterIP[57]=input[54]; InputAfterIP[58]=input[46]; InputAfterIP[59]=input[38]; InputAfterIP[60]=input[30]; InputAfterIP[61]=input[22]; InputAfterIP[62]=input[14]; InputAfterIP[63]=input[ 6];
    /*===========================================================================================================================================================================================================================*/

    /**
    * Process of the algorithm numberOfRounds.
    */
    for (int z = 0; z < numberOfRounds; z++) {
        /**
         * Expansion permutation ExP.
         */
        /*Expansion: ======================================================================================================================================================================================================================================*/
        char *InputAfterExP=new char[48];
        InputAfterExP[ 0]=(InputAfterIP+32)[31]; InputAfterExP[ 1]=(InputAfterIP+32)[ 0]; InputAfterExP[ 2]=(InputAfterIP+32)[ 1]; InputAfterExP[ 3]=(InputAfterIP+32)[ 2]; InputAfterExP[ 4]=(InputAfterIP+32)[ 3]; InputAfterExP[ 5]=(InputAfterIP+32)[ 4];
        InputAfterExP[ 6]=(InputAfterIP+32)[ 3]; InputAfterExP[ 7]=(InputAfterIP+32)[ 4]; InputAfterExP[ 8]=(InputAfterIP+32)[ 5]; InputAfterExP[ 9]=(InputAfterIP+32)[ 6]; InputAfterExP[10]=(InputAfterIP+32)[ 7]; InputAfterExP[11]=(InputAfterIP+32)[ 8];
        InputAfterExP[12]=(InputAfterIP+32)[ 7]; InputAfterExP[13]=(InputAfterIP+32)[ 8]; InputAfterExP[14]=(InputAfterIP+32)[ 9]; InputAfterExP[15]=(InputAfterIP+32)[10]; InputAfterExP[16]=(InputAfterIP+32)[11]; InputAfterExP[17]=(InputAfterIP+32)[12];
        InputAfterExP[18]=(InputAfterIP+32)[11]; InputAfterExP[19]=(InputAfterIP+32)[12]; InputAfterExP[20]=(InputAfterIP+32)[13]; InputAfterExP[21]=(InputAfterIP+32)[14]; InputAfterExP[22]=(InputAfterIP+32)[15]; InputAfterExP[23]=(InputAfterIP+32)[16];
        InputAfterExP[24]=(InputAfterIP+32)[15]; InputAfterExP[25]=(InputAfterIP+32)[16]; InputAfterExP[26]=(InputAfterIP+32)[17]; InputAfterExP[27]=(InputAfterIP+32)[18]; InputAfterExP[28]=(InputAfterIP+32)[19]; InputAfterExP[29]=(InputAfterIP+32)[20];
        InputAfterExP[30]=(InputAfterIP+32)[19]; InputAfterExP[31]=(InputAfterIP+32)[20]; InputAfterExP[32]=(InputAfterIP+32)[21]; InputAfterExP[33]=(InputAfterIP+32)[22]; InputAfterExP[34]=(InputAfterIP+32)[23]; InputAfterExP[35]=(InputAfterIP+32)[24];
        InputAfterExP[36]=(InputAfterIP+32)[23]; InputAfterExP[37]=(InputAfterIP+32)[24]; InputAfterExP[38]=(InputAfterIP+32)[25]; InputAfterExP[39]=(InputAfterIP+32)[26]; InputAfterExP[40]=(InputAfterIP+32)[27]; InputAfterExP[41]=(InputAfterIP+32)[28];
        InputAfterExP[42]=(InputAfterIP+32)[27]; InputAfterExP[43]=(InputAfterIP+32)[28]; InputAfterExP[44]=(InputAfterIP+32)[29]; InputAfterExP[45]=(InputAfterIP+32)[30]; InputAfterExP[46]=(InputAfterIP+32)[31]; InputAfterExP[47]=(InputAfterIP+32)[ 0];
        /*=================================================================================================================================================================================================================================================*/

        /**
         * Decide here which key will be used,
         *      method  >>> DECRYPTION
         *      !method >>> ENCRYPTION
         */
        char myKey = method ? (numberOfRounds - 1) - z : z;

        /**
         * XOR with key.
         */
        char *InputAfterKeyXor = new char[48];
        exor(InputAfterExP, keyEx[myKey], InputAfterKeyXor, 48);
        //Clean up, we don't need InputAfterExP anymore:
        delete[] InputAfterExP;

        /**
         * Proceed to S-Boxes.
         */
        char *InputAfterSBox = new char[32];
        for (int j = 0; j < 48; j += 6) {
            char k = j / 6;
            char sSel = s[k]
                    [(2 * InputAfterKeyXor[j]) + InputAfterKeyXor[j + 5]]
                    [(8 * InputAfterKeyXor[j + 1])+(4 * InputAfterKeyXor[j + 2])+(2 * InputAfterKeyXor[j + 3]) + InputAfterKeyXor[j + 4]];

            for (char i = 4; i > 0; sSel /= 2)
                InputAfterSBox[--i + (4 * k)] = sSel % 2;
        }
        //Clean up, we don't need InputAfterKeyXor anymore:
        delete[] InputAfterKeyXor;

        /**
         * Permutation (after s-box) PSB.
         */
        /*Permutation (after s-box): ========================================================================================================================*/
        char *InputAfterPSB=new char[32];
        InputAfterPSB[ 0]=InputAfterSBox[15]; InputAfterPSB[ 1]=InputAfterSBox[ 6]; InputAfterPSB[ 2]=InputAfterSBox[19]; InputAfterPSB[ 3]=InputAfterSBox[20];
        InputAfterPSB[ 4]=InputAfterSBox[28]; InputAfterPSB[ 5]=InputAfterSBox[11]; InputAfterPSB[ 6]=InputAfterSBox[27]; InputAfterPSB[ 7]=InputAfterSBox[16];
        InputAfterPSB[ 8]=InputAfterSBox[ 0]; InputAfterPSB[ 9]=InputAfterSBox[14]; InputAfterPSB[10]=InputAfterSBox[22]; InputAfterPSB[11]=InputAfterSBox[25];
        InputAfterPSB[12]=InputAfterSBox[ 4]; InputAfterPSB[13]=InputAfterSBox[17]; InputAfterPSB[14]=InputAfterSBox[30]; InputAfterPSB[15]=InputAfterSBox[ 9];
        InputAfterPSB[16]=InputAfterSBox[ 1]; InputAfterPSB[17]=InputAfterSBox[ 7]; InputAfterPSB[18]=InputAfterSBox[23]; InputAfterPSB[19]=InputAfterSBox[13];
        InputAfterPSB[20]=InputAfterSBox[31]; InputAfterPSB[21]=InputAfterSBox[26]; InputAfterPSB[22]=InputAfterSBox[ 2]; InputAfterPSB[23]=InputAfterSBox[ 8];
        InputAfterPSB[24]=InputAfterSBox[18]; InputAfterPSB[25]=InputAfterSBox[12]; InputAfterPSB[26]=InputAfterSBox[29]; InputAfterPSB[27]=InputAfterSBox[ 5];
        InputAfterPSB[28]=InputAfterSBox[21]; InputAfterPSB[29]=InputAfterSBox[10]; InputAfterPSB[30]=InputAfterSBox[ 3]; InputAfterPSB[31]=InputAfterSBox[24];
        /*===================================================================================================================================================*/
        //Clean up, we don't need InputAfterSBox anymore:
        delete[] InputAfterSBox;

        /**
         * XOR final, with the original input left side.
         */
        char *InputAfterFinalXor = new char[32];
        exor(InputAfterIP, InputAfterPSB, InputAfterFinalXor, 32);
        //Clean up, we don't need InputAfterPSB anymore:
        delete[] InputAfterPSB;

        /**
         * Re-Initializing for new round.
         */
        for (int k = 0; k < 32; k++) {
            InputAfterIP[k ] = InputAfterIP[k + 32];
            InputAfterIP[k + 32] = InputAfterFinalXor[k];
        }
        //Clean up, we don't need InputAfterFinalXor anymore:
        delete[] InputAfterFinalXor;
    }

    /**
     * Final permutation FP, inverse of initial pemutation before ending.
     */
    char *InputFinal = new char[64];
    for (int x = 0; x < 32; x++) {
        InputFinal[x ] = InputAfterIP[x + 32];
        InputFinal[x + 32] = InputAfterIP[x ];
    }
    //Clean up, we don't need InputAfterIP anymore:
    delete[] InputAfterIP;

    char *output = new char[64];
    /*Final permutation: ================================================================================================================================================================================================*/
    output[ 0]=InputFinal[39]; output[ 1]=InputFinal[ 7]; output[ 2]=InputFinal[47]; output[ 3]=InputFinal[15]; output[ 4]=InputFinal[55]; output[ 5]=InputFinal[23]; output[ 6]=InputFinal[63]; output[ 7]=InputFinal[31];
    output[ 8]=InputFinal[38]; output[ 9]=InputFinal[ 6]; output[10]=InputFinal[46]; output[11]=InputFinal[14]; output[12]=InputFinal[54]; output[13]=InputFinal[22]; output[14]=InputFinal[62]; output[15]=InputFinal[30];
    output[16]=InputFinal[37]; output[17]=InputFinal[ 5]; output[18]=InputFinal[45]; output[19]=InputFinal[13]; output[20]=InputFinal[53]; output[21]=InputFinal[21]; output[22]=InputFinal[61]; output[23]=InputFinal[29];
    output[24]=InputFinal[36]; output[25]=InputFinal[ 4]; output[26]=InputFinal[44]; output[27]=InputFinal[12]; output[28]=InputFinal[52]; output[29]=InputFinal[20]; output[30]=InputFinal[60]; output[31]=InputFinal[28];
    output[32]=InputFinal[35]; output[33]=InputFinal[ 3]; output[34]=InputFinal[43]; output[35]=InputFinal[11]; output[36]=InputFinal[51]; output[37]=InputFinal[19]; output[38]=InputFinal[59]; output[39]=InputFinal[27];
    output[40]=InputFinal[34]; output[41]=InputFinal[ 2]; output[42]=InputFinal[42]; output[43]=InputFinal[10]; output[44]=InputFinal[50]; output[45]=InputFinal[18]; output[46]=InputFinal[58]; output[47]=InputFinal[26];
    output[48]=InputFinal[33]; output[49]=InputFinal[ 1]; output[50]=InputFinal[41]; output[51]=InputFinal[ 9]; output[52]=InputFinal[49]; output[53]=InputFinal[17]; output[54]=InputFinal[57]; output[55]=InputFinal[25];
    output[56]=InputFinal[32]; output[57]=InputFinal[ 0]; output[58]=InputFinal[40]; output[59]=InputFinal[ 8]; output[60]=InputFinal[48]; output[61]=InputFinal[16]; output[62]=InputFinal[56]; output[63]=InputFinal[24];
    /*===================================================================================================================================================================================================================*/
    //Clean up, we don't need InputFinal anymore:
    delete[] InputFinal;
    char *outputDec = new char[9];
    outputDec[8] = 0;
    BinToDec(output, outputDec);
    delete[] output;
    return outputDec;
}

/**
 * ==============================================
 * @name ENCRYPT Function
 * @desc return a DES encrypted version of 'plainText'.
 * @param char*: a plain text.
 * @return char*: a DES cypher text.
 * ==============================================
 */
char* CDES::Encrypt(char *plainText) {
    return (DES(plainText));
}

/**
 * ==============================================
 * @name DECRYPT Function
 * @desc return a DES decrypted version of 'cipherText'.
 * @param char*: a DES cipher text.
 * @return char*: a plain text.
 * ==============================================
 */
char* CDES::Decrypt(char *cipherText) {
    return (DES(cipherText, true));
}

/**
 * ==============================================
 * @name CONSTRUCTOR
 * @desc Initialize number of rounds and the S-BOX.
 * @param int: Number of rounds [default: 16].
 * @return void
 * ==============================================
 */
CDES::CDES(int NumberOfRounds) {
    numberOfRounds = NumberOfRounds;
    /**
     * ---www.amahdy.com---
     * > S-Boxes, declare once
     */
    /* S-BOXES: =======================================================================================================================================================================================================================================*/
    s[0][0][0]=14; s[0][0][1]= 4; s[0][0][2]=13; s[0][0][3]= 1; s[0][0][4]= 2; s[0][0][5]=15; s[0][0][6]=11; s[0][0][7]= 8; s[0][0][8]= 3; s[0][0][9]=10; s[0][0][10]= 6; s[0][0][11]=12; s[0][0][12]= 5; s[0][0][13]= 9; s[0][0][14]= 0; s[0][0][15]= 7;
    s[0][1][0]= 0; s[0][1][1]=15; s[0][1][2]= 7; s[0][1][3]= 4; s[0][1][4]=14; s[0][1][5]= 2; s[0][1][6]=13; s[0][1][7]= 1; s[0][1][8]=10; s[0][1][9]= 6; s[0][1][10]=12; s[0][1][11]=11; s[0][1][12]= 9; s[0][1][13]= 5; s[0][1][14]= 3; s[0][1][15]= 8;
    s[0][2][0]= 4; s[0][2][1]= 1; s[0][2][2]=14; s[0][2][3]= 8; s[0][2][4]=13; s[0][2][5]= 6; s[0][2][6]= 2; s[0][2][7]=11; s[0][2][8]=15; s[0][2][9]=12; s[0][2][10]= 9; s[0][2][11]= 7; s[0][2][12]= 3; s[0][2][13]=10; s[0][2][14]= 5; s[0][2][15]= 0;
    s[0][3][0]=15; s[0][3][1]=12; s[0][3][2]= 8; s[0][3][3]= 2; s[0][3][4]= 4; s[0][3][5]= 9; s[0][3][6]= 1; s[0][3][7]= 7; s[0][3][8]= 5; s[0][3][9]=11; s[0][3][10]= 3; s[0][3][11]=14; s[0][3][12]=10; s[0][3][13]= 0; s[0][3][14]= 6; s[0][3][15]=13;
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    s[1][0][0]=15; s[1][0][1]= 1; s[1][0][2]= 8; s[1][0][3]=14; s[1][0][4]= 6; s[1][0][5]=11; s[1][0][6]= 3; s[1][0][7]= 4; s[1][0][8]= 9; s[1][0][9]= 7; s[1][0][10]= 2; s[1][0][11]=13; s[1][0][12]=12; s[1][0][13]= 0; s[1][0][14]= 5; s[1][0][15]=10;
    s[1][1][0]= 3; s[1][1][1]=13; s[1][1][2]= 4; s[1][1][3]= 7; s[1][1][4]=15; s[1][1][5]= 2; s[1][1][6]= 8; s[1][1][7]=14; s[1][1][8]=12; s[1][1][9]= 0; s[1][1][10]= 1; s[1][1][11]=10; s[1][1][12]= 6; s[1][1][13]= 9; s[1][1][14]=11; s[1][1][15]= 5;
    s[1][2][0]= 0; s[1][2][1]=14; s[1][2][2]= 7; s[1][2][3]=11; s[1][2][4]=10; s[1][2][5]= 4; s[1][2][6]=13; s[1][2][7]= 1; s[1][2][8]= 5; s[1][2][9]= 8; s[1][2][10]=12; s[1][2][11]= 6; s[1][2][12]= 9; s[1][2][13]= 3; s[1][2][14]= 2; s[1][2][15]=15;
    s[1][3][0]=13; s[1][3][1]= 8; s[1][3][2]=10; s[1][3][3]= 1; s[1][3][4]= 3; s[1][3][5]=15; s[1][3][6]= 4; s[1][3][7]= 2; s[1][3][8]=11; s[1][3][9]= 6; s[1][3][10]= 7; s[1][3][11]=12; s[1][3][12]= 0; s[1][3][13]= 5; s[1][3][14]=14; s[1][3][15]= 9;
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    s[2][0][0]=10; s[2][0][1]= 0; s[2][0][2]= 9; s[2][0][3]=14; s[2][0][4]= 6; s[2][0][5]= 3; s[2][0][6]=15; s[2][0][7]= 5; s[2][0][8]= 1; s[2][0][9]=13; s[2][0][10]=12; s[2][0][11]= 7; s[2][0][12]=11; s[2][0][13]= 4; s[2][0][14]= 2; s[2][0][15]= 8;
    s[2][1][0]=13; s[2][1][1]= 7; s[2][1][2]= 0; s[2][1][3]= 9; s[2][1][4]= 3; s[2][1][5]= 4; s[2][1][6]= 6; s[2][1][7]=10; s[2][1][8]= 2; s[2][1][9]= 8; s[2][1][10]= 5; s[2][1][11]=14; s[2][1][12]=12; s[2][1][13]=11; s[2][1][14]=15; s[2][1][15]= 1;
    s[2][2][0]=13; s[2][2][1]= 6; s[2][2][2]= 4; s[2][2][3]= 9; s[2][2][4]= 8; s[2][2][5]=15; s[2][2][6]= 3; s[2][2][7]= 0; s[2][2][8]=11; s[2][2][9]= 1; s[2][2][10]= 2; s[2][2][11]=12; s[2][2][12]= 5; s[2][2][13]=10; s[2][2][14]=14; s[2][2][15]= 7;
    s[2][3][0]= 1; s[2][3][1]=10; s[2][3][2]=13; s[2][3][3]= 0; s[2][3][4]= 6; s[2][3][5]= 9; s[2][3][6]= 8; s[2][3][7]= 7; s[2][3][8]= 4; s[2][3][9]=15; s[2][3][10]=14; s[2][3][11]= 3; s[2][3][12]=11; s[2][3][13]= 5; s[2][3][14]= 2; s[2][3][15]=12;
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    s[3][0][0]= 7; s[3][0][1]=13; s[3][0][2]=14; s[3][0][3]= 3; s[3][0][4]= 0; s[3][0][5]= 6; s[3][0][6]= 9; s[3][0][7]=10; s[3][0][8]= 1; s[3][0][9]= 2; s[3][0][10]= 8; s[3][0][11]= 5; s[3][0][12]=11; s[3][0][13]=12; s[3][0][14]= 4; s[3][0][15]=15;
    s[3][1][0]=13; s[3][1][1]= 8; s[3][1][2]=11; s[3][1][3]= 5; s[3][1][4]= 6; s[3][1][5]=15; s[3][1][6]= 0; s[3][1][7]= 3; s[3][1][8]= 4; s[3][1][9]= 7; s[3][1][10]= 2; s[3][1][11]=12; s[3][1][12]= 1; s[3][1][13]=10; s[3][1][14]=14; s[3][1][15]= 9;
    s[3][2][0]=10; s[3][2][1]= 6; s[3][2][2]= 9; s[3][2][3]= 0; s[3][2][4]=12; s[3][2][5]=11; s[3][2][6]= 7; s[3][2][7]=13; s[3][2][8]=15; s[3][2][9]= 1; s[3][2][10]= 3; s[3][2][11]=14; s[3][2][12]= 5; s[3][2][13]= 2; s[3][2][14]= 8; s[3][2][15]= 4;
    s[3][3][0]= 3; s[3][3][1]=15; s[3][3][2]= 0; s[3][3][3]= 6; s[3][3][4]=10; s[3][3][5]= 1; s[3][3][6]=13; s[3][3][7]= 8; s[3][3][8]= 9; s[3][3][9]= 4; s[3][3][10]= 5; s[3][3][11]=11; s[3][3][12]=12; s[3][3][13]= 7; s[3][3][14]= 2; s[3][3][15]=14;
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    s[4][0][0]= 2; s[4][0][1]=12; s[4][0][2]= 4; s[4][0][3]= 1; s[4][0][4]= 7; s[4][0][5]=10; s[4][0][6]=11; s[4][0][7]= 6; s[4][0][8]= 8; s[4][0][9]= 5; s[4][0][10]= 3; s[4][0][11]=15; s[4][0][12]=13; s[4][0][13]= 0; s[4][0][14]=14; s[4][0][15]= 9;
    s[4][1][0]=14; s[4][1][1]=11; s[4][1][2]= 2; s[4][1][3]=12; s[4][1][4]= 4; s[4][1][5]= 7; s[4][1][6]=13; s[4][1][7]= 1; s[4][1][8]= 5; s[4][1][9]= 0; s[4][1][10]=15; s[4][1][11]=10; s[4][1][12]= 3; s[4][1][13]= 9; s[4][1][14]= 8; s[4][1][15]= 6;
    s[4][2][0]= 4; s[4][2][1]= 2; s[4][2][2]= 1; s[4][2][3]=11; s[4][2][4]=10; s[4][2][5]=13; s[4][2][6]= 7; s[4][2][7]= 8; s[4][2][8]=15; s[4][2][9]= 9; s[4][2][10]=12; s[4][2][11]= 5; s[4][2][12]= 6; s[4][2][13]= 3; s[4][2][14]= 0; s[4][2][15]=14;
    s[4][3][0]=11; s[4][3][1]= 8; s[4][3][2]=12; s[4][3][3]= 7; s[4][3][4]= 1; s[4][3][5]=14; s[4][3][6]= 2; s[4][3][7]=13; s[4][3][8]= 6; s[4][3][9]=15; s[4][3][10]= 0; s[4][3][11]= 9; s[4][3][12]=10; s[4][3][13]= 4; s[4][3][14]= 5; s[4][3][15]= 3;
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    s[5][0][0]=12; s[5][0][1]= 1; s[5][0][2]=10; s[5][0][3]=15; s[5][0][4]= 9; s[5][0][5]= 2; s[5][0][6]= 6; s[5][0][7]= 8; s[5][0][8]= 0; s[5][0][9]=13; s[5][0][10]= 3; s[5][0][11]= 4; s[5][0][12]=14; s[5][0][13]= 7; s[5][0][14]= 5; s[5][0][15]=11;
    s[5][1][0]=10; s[5][1][1]=15; s[5][1][2]= 4; s[5][1][3]= 2; s[5][1][4]= 7; s[5][1][5]=12; s[5][1][6]= 9; s[5][1][7]= 5; s[5][1][8]= 6; s[5][1][9]= 1; s[5][1][10]=13; s[5][1][11]=14; s[5][1][12]= 0; s[5][1][13]=11; s[5][1][14]= 3; s[5][1][15]= 8;
    s[5][2][0]= 9; s[5][2][1]=14; s[5][2][2]=15; s[5][2][3]= 5; s[5][2][4]= 2; s[5][2][5]= 8; s[5][2][6]=12; s[5][2][7]= 3; s[5][2][8]= 7; s[5][2][9]= 0; s[5][2][10]= 4; s[5][2][11]=10; s[5][2][12]= 1; s[5][2][13]=13; s[5][2][14]=11; s[5][2][15]= 6;
    s[5][3][0]= 4; s[5][3][1]= 3; s[5][3][2]= 2; s[5][3][3]=12; s[5][3][4]= 9; s[5][3][5]= 5; s[5][3][6]=15; s[5][3][7]=10; s[5][3][8]=11; s[5][3][9]=14; s[5][3][10]= 1; s[5][3][11]= 7; s[5][3][12]= 6; s[5][3][13]= 0; s[5][3][14]= 8; s[5][3][15]=13;
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    s[6][0][0]= 4; s[6][0][1]=11; s[6][0][2]= 2; s[6][0][3]=14; s[6][0][4]=15; s[6][0][5]= 0; s[6][0][6]= 8; s[6][0][7]=13; s[6][0][8]= 3; s[6][0][9]=12; s[6][0][10]= 9; s[6][0][11]= 7; s[6][0][12]= 5; s[6][0][13]=10; s[6][0][14]= 6; s[6][0][15]= 1;
    s[6][1][0]=13; s[6][1][1]= 0; s[6][1][2]=11; s[6][1][3]= 7; s[6][1][4]= 4; s[6][1][5]= 9; s[6][1][6]= 1; s[6][1][7]=10; s[6][1][8]=14; s[6][1][9]= 3; s[6][1][10]= 5; s[6][1][11]=12; s[6][1][12]= 2; s[6][1][13]=15; s[6][1][14]= 8; s[6][1][15]= 6;
    s[6][2][0]= 1; s[6][2][1]= 4; s[6][2][2]=11; s[6][2][3]=13; s[6][2][4]=12; s[6][2][5]= 3; s[6][2][6]= 7; s[6][2][7]=14; s[6][2][8]=10; s[6][2][9]=15; s[6][2][10]= 6; s[6][2][11]= 8; s[6][2][12]= 0; s[6][2][13]= 5; s[6][2][14]= 9; s[6][2][15]= 2;
    s[6][3][0]= 6; s[6][3][1]=11; s[6][3][2]=13; s[6][3][3]= 8; s[6][3][4]= 1; s[6][3][5]= 4; s[6][3][6]=10; s[6][3][7]= 7; s[6][3][8]= 9; s[6][3][9]= 5; s[6][3][10]= 0; s[6][3][11]=15; s[6][3][12]=14; s[6][3][13]= 2; s[6][3][14]= 3; s[6][3][15]=12;
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    s[7][0][0]=13; s[7][0][1]= 2; s[7][0][2]= 8; s[7][0][3]= 4; s[7][0][4]= 6; s[7][0][5]=15; s[7][0][6]=11; s[7][0][7]= 1; s[7][0][8]=10; s[7][0][9]= 9; s[7][0][10]= 3; s[7][0][11]=14; s[7][0][12]= 5; s[7][0][13]= 0; s[7][0][14]=12; s[7][0][15]= 7;
    s[7][1][0]= 1; s[7][1][1]=15; s[7][1][2]=13; s[7][1][3]= 8; s[7][1][4]=10; s[7][1][5]= 3; s[7][1][6]= 7; s[7][1][7]= 4; s[7][1][8]=12; s[7][1][9]= 5; s[7][1][10]= 6; s[7][1][11]=11; s[7][1][12]= 0; s[7][1][13]=14; s[7][1][14]= 9; s[7][1][15]= 2;
    s[7][2][0]= 7; s[7][2][1]=11; s[7][2][2]= 4; s[7][2][3]= 1; s[7][2][4]= 9; s[7][2][5]=12; s[7][2][6]=14; s[7][2][7]= 2; s[7][2][8]= 0; s[7][2][9]= 6; s[7][2][10]=10; s[7][2][11]=13; s[7][2][12]=15; s[7][2][13]= 3; s[7][2][14]= 5; s[7][2][15]= 8;
    s[7][3][0]= 2; s[7][3][1]= 1; s[7][3][2]=14; s[7][3][3]= 7; s[7][3][4]= 4; s[7][3][5]=10; s[7][3][6]= 8; s[7][3][7]=13; s[7][3][8]=15; s[7][3][9]=12; s[7][3][10]= 9; s[7][3][11]=10; s[7][3][12]= 3; s[7][3][13]= 5; s[7][3][14]= 6; s[7][3][15]=11;
    /*=================================================================================================================================================================================================================================================*/
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
    for (int i = 0; i < numberOfRounds; i++)
        delete[] keyEx[i];
    delete[] keyEx;
    return;
}
