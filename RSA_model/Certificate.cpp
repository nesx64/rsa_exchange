#include "Certificate.h"

Certificate::Certificate() = default;
Certificate::~Certificate() = default;

Certificate::Certificate(UserModel* u, cpp_int sign) {
    this->user = u;
    this->pubkey = u->getPublicKey();
    this->privkey = u->getPrivateKey();
    this->signature = sign;
}

UserModel* Certificate::getUser() const {
    return user;
}

PublicKeyModel* Certificate::getPublicKey() const {
    return pubkey;
}

PrivateKeyModel* Certificate::getPrivateKey() const {
    return privkey;
}

cpp_int Certificate::getSignature() const {
    return signature;
}