#ifndef CRYPT
#define CRYPT

/**
 * ==============================================
 * @name CRYPT ABSTRACT CLASS
 * @desc This is the abstract cryptography class, from here inherit any algorithm class.
 * @data empty
 * @member empty
 * @public %1 virtual void: key generator function.
 *         %2 virtual void*: encrypt function.
 *         %3 virtual void*: decrypt function.
 * ==============================================
 */
class Crypt {
public:
    virtual void KeyGen(const void*)=0;
    virtual void* Encrypt(const void*)=0;
    virtual void* Decrypt(const void*)=0;
};

#endif
