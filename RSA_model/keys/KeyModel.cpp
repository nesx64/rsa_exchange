#include "KeyModel.h"

KeyModel::KeyModel() {
  this->user = nullptr;
  this->value = 0;
}

UserModel* KeyModel::getUser() {
    return this->user;
}

cpp_int KeyModel::getValue() {
    return this->value;
}

void KeyModel::setValue(cpp_int v) {
    this->value = v;
}

KeyModel::~KeyModel() = default;
