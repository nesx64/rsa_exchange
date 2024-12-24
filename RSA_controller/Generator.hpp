#include <fstream>

#include "../RSA_model/UserModel.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <openssl/sha.h>

#include "../RSA_model/keys/PublicKeyModel.h"
#include "../RSA_model/keys/PrivateKeyModel.h"

using namespace boost::multiprecision;

class Generator {
    Generator() = default;
    ~Generator();
    static Generator* instance;

    bool testPrime(cpp_int x) const;
    cpp_int pgcd(cpp_int a, cpp_int b) const;
    cpp_int bezout(cpp_int a, cpp_int b) const;
    cpp_int randomBigInteger(const cpp_int& min, const cpp_int& max) const;
    cpp_int secureRandomBigInteger(int bitLength) const;
    cpp_int randPrime();
    cpp_int phi(cpp_int p, cpp_int q) const;

    public:
        static Generator* getGenerator();
        friend Generator* getGenerator();
        cpp_int modularPow(cpp_int a, cpp_int e, cpp_int n) const;
        bool generateKeysFor(UserModel* u);
        cpp_int hash(QString message, cpp_int n) const;
        cpp_int signMessage(cpp_int hash, PrivateKeyModel* privkey, cpp_int n) const;
        bool testKeys(const UserModel* u, const cpp_int& phi) const;
        bool checkSign(cpp_int sign, cpp_int hash, PublicKeyModel* pubkey, cpp_int n) const;
};