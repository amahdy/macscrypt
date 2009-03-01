#ifndef CRYPT
#define CRYPT

/**
 * ==============================================
 * @name CRYPT ABSTRACT CLASS
 * @desc This is the abstract cryptography class, from here inherit any algorithm class.
 * @data empty
 * @member empty
 * @public %1 void: key generator function.
 *         %2 char*: encrypt function.
 *         %3 char*: decrypt function.
 * ==============================================
 */
class Crypt {
public:
    virtual void KeyGen(const char*)=0;
    virtual char* Encrypt(char*)=0;
    virtual char* Decrypt(char*)=0;
};

#endif
