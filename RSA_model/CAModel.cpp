//
// Created by loan on 23/12/24.
//

#include "CAModel.h"

#include "../RSA_controller/Generator.hpp"
#include "keys/PrivateKeyModel.h"

CAModel::CAModel() = default;
CAModel::~CAModel() = default;

CAModel::CAModel(QString n, PrivateKeyModel* pk) : UserModel(n, pk) {}

CAModel::CAModel(QString n) : UserModel(n) {}

void CAModel::addCertificate(Certificate c) {
    this->certifs.insert(c);
}

Certificate CAModel::getCertificateOf(UserModel* u) {
    for (auto c : this->certifs) {
        if (c.getUser()->getName() == c.getUser()->getName()) {
            return c;
        }
    }
    return Certificate();
}


bool CAModel::verifyCertificate(Certificate c) const {
    cpp_int certificateHash = Generator::getGenerator()->hash(c.getPublicKey()->getValue().str().data(),this->getN());
    return Generator::getGenerator()->checkSign(c.getSignature(), certificateHash, this->getPublicKey(), this->getN());
}


