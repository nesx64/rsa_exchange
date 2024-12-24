//
// Created by loan on 23/12/24.
//

#ifndef CAMODEL_H
#define CAMODEL_H

#include "UserModel.h"
#include <QSet>

#include "Certificate.h"

class CAModel : public UserModel {
    QSet<Certificate> certifs;
    public:
        CAModel();
        ~CAModel();
        CAModel(QString n, PrivateKeyModel* pk);
        CAModel(QString n);
        void addCertificate(Certificate c);
        Certificate getCertificateOf(UserModel* u);
        bool verifyCertificate(Certificate c) const;
};

#endif //CAMODEL_H
