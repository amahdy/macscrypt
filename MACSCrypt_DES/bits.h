/* 
 * File:   bits.h
 * Author: Amahdy
 *
 * Created on March 29, 2009, 8:49 PM
 */

#ifndef _BITS_H
#define	_BITS_H

//#ifdef	__cplusplus
//extern "C" {
//#endif

//#include <iostream>

struct bits {
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;

//    void disp() {
//        if (b0 == 0) std::cout<<0; else std::cout<<1;
//        if (b1 == 0) std::cout<<0; else std::cout<<1;
//        if (b2 == 0) std::cout<<0; else std::cout<<1;
//        if (b3 == 0) std::cout<<0; else std::cout<<1;
//        if (b4 == 0) std::cout<<0; else std::cout<<1;
//        if (b5 == 0) std::cout<<0; else std::cout<<1;
//        if (b6 == 0) std::cout<<0; else std::cout<<1;
//        if (b7 == 0) std::cout<<0; else std::cout<<1;
//        std::cout << ' ';
//    }

    static unsigned char getBit(bits* a, unsigned char pos) {
        unsigned char pos1 = pos / 8;
        unsigned char pos2 = pos % 8;

        if(pos2 == 0) if(a[pos1].b0 == 0) return 0; else return 1;
        if(pos2 == 1) if(a[pos1].b1 == 0) return 0; else return 1;
        if(pos2 == 2) if(a[pos1].b2 == 0) return 0; else return 1;
        if(pos2 == 3) if(a[pos1].b3 == 0) return 0; else return 1;
        if(pos2 == 4) if(a[pos1].b4 == 0) return 0; else return 1;
        if(pos2 == 5) if(a[pos1].b5 == 0) return 0; else return 1;
        if(pos2 == 6) if(a[pos1].b6 == 0) return 0; else return 1;
        if(pos2 == 7) if(a[pos1].b7 == 0) return 0; else return 1;
    }

    static void setBit(bits* a, unsigned char pos, unsigned char val) {
        unsigned char pos1 = pos / 8;
        unsigned char pos2 = pos % 8;

        if(pos2 == 0) a[pos1].b0 = (val == 0)? 0:1;
        else if(pos2 == 1) a[pos1].b1 = (val == 0)? 0:1;
        else if(pos2 == 2) a[pos1].b2 = (val == 0)? 0:1;
        else if(pos2 == 3) a[pos1].b3 = (val == 0)? 0:1;
        else if(pos2 == 4) a[pos1].b4 = (val == 0)? 0:1;
        else if(pos2 == 5) a[pos1].b5 = (val == 0)? 0:1;
        else if(pos2 == 6) a[pos1].b6 = (val == 0)? 0:1;
        else if(pos2 == 7) a[pos1].b7 = (val == 0)? 0:1;
    }

    static void xBit(bits* a, unsigned char posA, bits* b, unsigned char posB) {
        bits::setBit(a, posA, bits::getBit(b, posB));
        return;
    }

    bits& operator=(const bits &rhs) {
        b0 = rhs.b0;
        b1 = rhs.b1;
        b2 = rhs.b2;
        b3 = rhs.b3;
        b4 = rhs.b4;
        b5 = rhs.b5;
        b6 = rhs.b6;
        b7 = rhs.b7;
        return *this;
    }

    bits& operator=(unsigned char rhs) {
        b7 = rhs%2;
        rhs /= 2;
        b6 = rhs%2;
        rhs /= 2;
        b5 = rhs%2;
        rhs /= 2;
        b4 = rhs%2;
        rhs /= 2;
        b3 = rhs%2;
        rhs /= 2;
        b2 = rhs%2;
        rhs /= 2;
        b1 = rhs%2;
        rhs /= 2;
        b0 = rhs%2;
        return *this;
    }

    unsigned char toChar() {
        return (unsigned char)(128 * b0
                             +  64 * b1
                             +  32 * b2
                             +  16 * b3
                             +   8 * b4
                             +   4 * b5
                             +   2 * b6
                             +       b7);
    }

    bits& operator^(const bits &other) {
        b0 ^= other.b0;
        b1 ^= other.b1;
        b2 ^= other.b2;
        b3 ^= other.b3;
        b4 ^= other.b4;
        b5 ^= other.b5;
        b6 ^= other.b6;
        b7 ^= other.b7;
        return *this;
    }
};

//#ifdef	__cplusplus
//}
//#endif

#endif	/* _BITS_H */

