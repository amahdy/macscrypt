/* 
 * File:   main.cpp
 * Author: Amahdy
 *
 * Created on March 1, 2009, 8:23 PM
 */

#include <stdlib.h>
#include <iostream>
#include "des.h"

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
    char DEC8_KEY[]="01234567";
    int NUMBER_OF_ROUNDS=16;
    CDES DES(NUMBER_OF_ROUNDS);
    DES.KeyGen(DEC8_KEY);

    char* PLAINTEXT;
    char* CYPHERTEXT;

    PLAINTEXT = new char[9];
    PLAINTEXT = "01234567";

    CYPHERTEXT = DES.Encrypt(PLAINTEXT);
    std::cout<<"Cypher: ";
    disp(CYPHERTEXT, 9);
    std::cout<<std::endl;

//    CYPHERTEXT = new char[9];
//    CYPHERTEXT = "01234567";

    PLAINTEXT = DES.Decrypt(CYPHERTEXT);
    std::cout<<"Plain: ";
    disp(PLAINTEXT, 9);
    std::cout<<std::endl;
    
    return (EXIT_SUCCESS);
}
