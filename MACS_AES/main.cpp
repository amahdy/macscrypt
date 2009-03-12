/*
 * File:   main.cpp
 * Author: paula
 *
 */

#include <stdlib.h>
#include <iostream>
#include "caes.h"

/*
 * displayer
 */
void disp(char* data, int length) {
    for (int i = 0; i < length; i++) {
        std::cout<<data[i];
    }
}
/*
 * entry point
 */
int main(int argc, char** argv) {

    char *key = "01234567890123456789";
    int NUMBER_OF_ROUNDS=16;
    CAES AES(NUMBER_OF_ROUNDS);
    AES.KeyGen(key);


    char *plainText = new char[17];
    plainText = "paula mansour fouad";

    char *cypherText = AES.Encrypt(plainText);
    std::cout<<"Cypher: ";
    disp(cypherText, 17);
    std::cout<<std::endl;


    plainText = AES.Decrypt(cypherText);
    std::cout<<"Plain: ";
    disp(plainText, 17);
    std::cout<<std::endl;

    return (EXIT_SUCCESS);
}