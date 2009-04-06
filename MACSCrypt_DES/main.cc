/* 
 * File:   main.cpp
 * Author: Amahdy
 *
 * Created on March 1, 2009, 8:23 PM
 */

#include <stdlib.h>
#include <iostream>
#include "cdes.h"

/*
 * displayer
 */
void disp(unsigned char* data, int length) {
    for (int i = 0; i < length; i++) {
        std::cout<<(int)data[i]<<".";
    }
}

/*
 * entry point
 */
int main(int argc, char** argv) {
    unsigned char DEC8_KEY[]="01234567";
    int NUMBER_OF_ROUNDS=16;
    CDES DES(NUMBER_OF_ROUNDS);
    DES.KeyGen(DEC8_KEY);

    unsigned char* PLAINTEXT = (unsigned char*)"01234567";
    unsigned char* CYPHERTEXT = new unsigned char[8];

    CYPHERTEXT = DES.Encrypt(PLAINTEXT);
    std::cout<<"Cypher: "; disp(CYPHERTEXT, 8); std::cout<<std::endl;

    PLAINTEXT = DES.Decrypt(CYPHERTEXT);
    std::cout<<"Plain: "; disp(PLAINTEXT, 8); std::cout<<std::endl;

    return (EXIT_SUCCESS);
}
