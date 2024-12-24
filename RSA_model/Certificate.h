#ifndef CERTIFICATE_H
#define CERTIFICATE_H
#include "UserModel.h"
#include "QHash"

class Certificate {
    UserModel* user{};
    PublicKeyModel* pubkey{};
    PrivateKeyModel* privkey{};
    cpp_int signature{};
    public :
        Certificate();
        ~Certificate();
        bool operator==(const Certificate& other) const {
            return this->user->getName() == other.user->getName() && this->getSignature() == other.getSignature();
        }
        Certificate(UserModel* u, cpp_int sign);
        UserModel* getUser() const;
        PublicKeyModel* getPublicKey() const;
        PrivateKeyModel* getPrivateKey() const;
        cpp_int getSignature() const;
};

inline uint qHash(const Certificate& key, uint seed = 0) {
    return qHash(key.getUser(), seed) ^ qHash(static_cast<char>(key.getSignature()), seed);
}

#endif //CERTIFICATE_H
