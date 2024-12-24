#include "PrivateKeyModel.h"

PrivateKeyModel::PrivateKeyModel(UserModel* u, cpp_int v) : KeyModel(){
    this->user = u;
    this->value = v;
}

PrivateKeyModel::PrivateKeyModel(UserModel* u) : KeyModel(){
    this->user = u;
    u->addPrivateKey(this);
}

PrivateKeyModel::~PrivateKeyModel() = default;
