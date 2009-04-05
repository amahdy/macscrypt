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

class bits {
public:
    unsigned char b7:1;
    unsigned char b6:1;
    unsigned char b5:1;
    unsigned char b4:1;
    unsigned char b3:1;
    unsigned char b2:1;
    unsigned char b1:1;
    unsigned char b0:1;

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
        switch(pos % 8) {
            case 0: return(a[pos / 8].b0 == 1);
            case 1: return(a[pos / 8].b1 == 1);
            case 2: return(a[pos / 8].b2 == 1);
            case 3: return(a[pos / 8].b3 == 1);
            case 4: return(a[pos / 8].b4 == 1);
            case 5: return(a[pos / 8].b5 == 1);
            case 6: return(a[pos / 8].b6 == 1);
            case 7: return(a[pos / 8].b7 == 1);
        }
    }

    static void setBit(bits* a, unsigned char pos, unsigned char val) {
        switch(pos % 8) {
            case 0: a[pos / 8].b0 = (val == 0)? 0:1; break;
            case 1: a[pos / 8].b1 = (val == 0)? 0:1; break;
            case 2: a[pos / 8].b2 = (val == 0)? 0:1; break;
            case 3: a[pos / 8].b3 = (val == 0)? 0:1; break;
            case 4: a[pos / 8].b4 = (val == 0)? 0:1; break;
            case 5: a[pos / 8].b5 = (val == 0)? 0:1; break;
            case 6: a[pos / 8].b6 = (val == 0)? 0:1; break;
            case 7: a[pos / 8].b7 = (val == 0)? 0:1; break;
        }
        return;
    }

    static void xBit(bits* a, unsigned char posA, bits* b, unsigned char posB) {
        bits::setBit(a, posA, bits::getBit(b, posB));
        return;
    }

// not needed, just define a bits* and cast memory!
//    bits& operator=(unsigned char rhs) {
//        b7 = rhs%2;
//        rhs /= 2;
//        b6 = rhs%2;
//        rhs /= 2;
//        b5 = rhs%2;
//        rhs /= 2;
//        b4 = rhs%2;
//        rhs /= 2;
//        b3 = rhs%2;
//        rhs /= 2;
//        b2 = rhs%2;
//        rhs /= 2;
//        b1 = rhs%2;
//        rhs /= 2;
//        b0 = rhs%2;
//        return *this;
//    }

// not needed, just define a char* and cast memory!
//    operator unsigned char() const {
//        return (unsigned char)(128 * b0
//                             +  64 * b1
//                             +  32 * b2
//                             +  16 * b3
//                             +   8 * b4
//                             +   4 * b5
//                             +   2 * b6
//                             +       b7);
//    }

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
