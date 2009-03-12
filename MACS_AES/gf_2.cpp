/* 
 * File:   gf_2.cpp
 * Author: Paula
 * 
 * Created on March 12, 2009, 4:12 PM
 */

#include "gf_2.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//			Finite Fields Of the Form GF(2n)
//	Done by : Paula Mansour Fouad
//	Date	: 21-01-2008
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

unsigned char GF_2_::MultiplyBy2GF2(unsigned char byte) {
    oneb = 0x1b;
    bool b7 = (byte >= 0x80) ? 1 : 0;
    byte = byte << 1;
    if (b7)
        return byte^oneb;
    else
        return byte;
}

unsigned char GF_2_::MultiplyBy3GF2(unsigned char byte) {
    return byte^MultiplyBy2GF2(byte);
}

unsigned char GF_2_::MultiplyGF2(unsigned char byte, unsigned char b) {
    unsigned char buffer[4];
    buffer[0] = byte;
    for (int i = 1; i < 4; i++)
        buffer[i] = MultiplyBy2GF2(buffer[i - 1]);
    switch (b) {
        case 0x09: return buffer[0]^buffer[3];
            break;
        case 0x0b: return buffer[0]^buffer[1]^buffer[3];
            break;
        case 0x0d: return buffer[0]^buffer[2]^buffer[3];
            break;
        case 0x0e: return buffer[1]^buffer[2]^buffer[3];
            break;
        default:return 0x00;
    }
}

