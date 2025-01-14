#ifndef USERMODEL_H
#define USERMODEL_H

#include <QSet>
#include <qstring.h>
#include<string>

#include <boost/multiprecision/cpp_int.hpp>

#include "Message.h"

using namespace boost::multiprecision;

class PrivateKeyModel;
class PublicKeyModel;

class UserModel {
    private:
        QString name;
        PrivateKeyModel* privateKey;
        PublicKeyModel* publicKey;
        cpp_int n;
        cpp_int phi;
        QSet<Message*> messages;
    public:
        UserModel();
        UserModel(QString n, PrivateKeyModel* pk);
        UserModel(QString n);

        QString getName();

        PrivateKeyModel* getPrivateKey() const;
        PublicKeyModel* getPublicKey() const;
        cpp_int getN() const;
        void setN(cpp_int n);
        cpp_int getPhi() const;
        void setPhi(cpp_int phi);

        QSet<Message*> getMessages();

        void addPrivateKey(PrivateKeyModel* pk);
        void addPublicKey(PublicKeyModel* pk);
        void removeKeys();
        bool operator<(const UserModel& other) const;
};

#endif //USERMODEL_H
