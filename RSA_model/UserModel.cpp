#include "UserModel.h"

#include "keys/PublicKeyModel.h"
#include "keys/PrivateKeyModel.h"

UserModel::UserModel() : privateKey(nullptr), publicKey(nullptr) {}

UserModel::UserModel(QString n, PrivateKeyModel* pk) {
  name = n;
  privateKey = pk;
  publicKey = nullptr;
}

UserModel::UserModel(QString n) {
  this->name = n;
  privateKey = nullptr;
  publicKey = nullptr;
}

QString UserModel::getName() {
	return name;
}

PrivateKeyModel* UserModel::getPrivateKey() const {
  return privateKey;
}

PublicKeyModel* UserModel::getPublicKey() const {
  return publicKey;
}

cpp_int UserModel::getN() const {
	return n;
}

void UserModel::setN(cpp_int n) {
  this->n = n;
}

cpp_int UserModel::getPhi() const {
  return phi;
}

void UserModel::setPhi(cpp_int phi) {
  this->phi = phi;
}

void UserModel::addPrivateKey(PrivateKeyModel* pk) {
  privateKey = pk;
}

void UserModel::addPublicKey(PublicKeyModel* pk) {
  publicKey = pk;
}

void UserModel::removeKeys() {
  if (privateKey) {
    delete privateKey;
    privateKey = nullptr;
  }
  if (publicKey) {
    delete publicKey;
    publicKey = nullptr;
  }
}

bool UserModel::operator<(const UserModel &other) const {
  return name < other.name;
}

