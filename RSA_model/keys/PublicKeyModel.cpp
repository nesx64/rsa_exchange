#include "PublicKeyModel.h"

PublicKeyModel::PublicKeyModel(UserModel* u, cpp_int e) : KeyModel() {
    this->user = u;
    this->value = e;
}
PublicKeyModel::PublicKeyModel(UserModel* u) : KeyModel() {
    this->user = u;
    u->addPublicKey(this);
}

PublicKeyModel::~PublicKeyModel() = default;