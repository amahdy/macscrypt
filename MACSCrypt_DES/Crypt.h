#ifndef CRYPT
#define CRYPT

/**
 * ==============================================
 * @name CRYPT ABSTRACT CLASS
 * @desc This is the abstract cryptography class, from here inherit any algorithm class.
 * @data empty
 * @member empty
 * @public %1 virtual void: key generator function.
 *         %2 virtual unsigned char*: encrypt function.
 *         %3 virtual unsigned char*: decrypt function.
 * ==============================================
 */
class Crypt {
public:
    virtual void KeyGen(const unsigned char*)=0;
    virtual unsigned char* Encrypt(const unsigned char*)=0;
    virtual unsigned char* Decrypt(const unsigned char*)=0;
};

#endif
