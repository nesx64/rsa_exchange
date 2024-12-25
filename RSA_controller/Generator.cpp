#include "Generator.hpp"

#include <fstream>
#include <openssl/sha.h>

#include "RSA_model/keys/PrivateKeyModel.h"
#include "RSA_model/keys/PublicKeyModel.h"

Generator::~Generator() = default;

Generator* Generator::instance = nullptr;

Generator* Generator::getGenerator() {
    if (!instance) {
        instance = new Generator();
    }
    return instance;
}

bool Generator::testPrime(cpp_int x) const {
        return miller_rabin_test(x,75);
}

cpp_int Generator::pgcd(cpp_int a, cpp_int b) const {
    return boost::multiprecision::gcd(a,b);
}

cpp_int Generator::bezout(cpp_int a, cpp_int b) const {
    cpp_int a0 = a, b0 = b;
    cpp_int p = 1, q = 0;
    cpp_int r = 0, s = 1;

    while (b != 0) {
        cpp_int c = a % b;
        cpp_int quotient = a / b;
        a = b;
        b = c;

        cpp_int newR = p - quotient * r;
        cpp_int newS = q - quotient * s;
        p = r;
        q = s;
        r = newR;
        s = newS;
    }
    if (p < 0) {
        p = p + b0;
    }
    return p;
}

cpp_int Generator::randomBigInteger(const cpp_int& min, const cpp_int& max) const {
    if (min >= max) {
        throw std::invalid_argument("Min must be less than max\nWas called with min = "
            + min.str() + " and max = " + max.str());
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    cpp_int range = max - min;
    int bitLength = msb(range) + 1;
    cpp_int randomValue;
    do {
        randomValue = 0;
        for (int i = 0; i < bitLength; ++i) {
            if (gen() % 2) {
                randomValue |= cpp_int(1) << i;
            }
        }
    } while (randomValue >= range);
    return randomValue + min;
}

cpp_int Generator::secureRandomBigInteger(int bitLength) const {
    cpp_int result = 0;
    std::ifstream urandom("/dev/urandom", std::ios::binary);
    int bytes = (bitLength + 7) / 8;
    std::vector<unsigned char> buffer(bytes);
    if (urandom) {
        urandom.read(reinterpret_cast<char*>(buffer.data()), bytes);
        urandom.close();
        for (int i = 0; i < bytes; ++i) {
            result = (result << 8) | buffer[i];
        }
        result &= (cpp_int(1) << bitLength) - 1;
        result |= cpp_int(1) << (bitLength - 1);
    }
    return result;
}

cpp_int Generator::randPrime() {
    int bitLength = 256;
    cpp_int res = secureRandomBigInteger(bitLength);
    while(!testPrime(res)) {
        res = secureRandomBigInteger(bitLength);
    }
    return res;
}

cpp_int Generator::phi(cpp_int p, cpp_int q) const {
    return (p-1)*(q-1);
}

cpp_int Generator::modularPow(cpp_int a, cpp_int e, cpp_int n) const {
     cpp_int p = 1;
     a = a%n;
     while (e > 0) {
         if (e%2 == 1) {
             p = (p*a)%n;
         }
         a=(a*a)%n;
         e = e >> 1;
     }
     return p;
}

bool Generator::generateKeysFor(UserModel* u) {
     cpp_int p = randPrime();
     cpp_int q = randPrime();
     cpp_int n = p*q;
     cpp_int phi = this->phi(p,q);
     cpp_int e = randomBigInteger(2, phi-1);
     while (pgcd(e, phi) != 1) {
         e = randomBigInteger(2, phi-1);
     }
     cpp_int d = bezout(e,phi);
     u->addPublicKey(new PublicKeyModel(u,e));
     u->addPrivateKey(new PrivateKeyModel(u,d));
     if (testKeys(u, phi)) {
          u->setN(n);
          u->setPhi(phi);
          return true;
     }
     u->removeKeys();
     return false;
}
bool Generator::testKeys(const UserModel* u, const cpp_int& phi) const {
     const cpp_int e = u->getPublicKey()->getValue();
     const cpp_int d = u->getPrivateKey()->getValue();
     return e*d%phi == 1;
}

cpp_int Generator::hash(QString message, cpp_int n) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    QByteArray msgBytes = message.toUtf8();
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, msgBytes.constData(), msgBytes.length());
    SHA256_Final(hash, &sha256);
    cpp_int hashed = 0;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashed = (hashed << 8) | hash[i];
    }
    return hashed%n;
}

cpp_int Generator::signMessage(cpp_int hash, PrivateKeyModel* privkey, cpp_int n) const {
    return modularPow(hash,privkey->getValue(),n);
}

bool Generator::checkSign(cpp_int sign, cpp_int hash, PublicKeyModel* pubkey, cpp_int n) const {
    return modularPow(sign, pubkey->getValue(), n) == hash;
}