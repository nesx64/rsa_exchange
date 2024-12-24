#ifndef RSACONTROLLER_H
#define RSACONTROLLER_H

#include "../RSA_model/RSAModel.h"
#include "../RSA_model/Certificate.h"
#include "../RSA_model/CAModel.h"

class RSAController {
    static const std::string MESSAGE_SEPARATOR;
    Certificate gatherDataForCertificate(UserModel* u, CAModel* ca) const;
    protected:
        RSAModel* model{};
    public:
        RSAController();
        ~RSAController();
        explicit RSAController(RSAModel* m);
        void setKeysFor(UserModel* u) const;
        void sendMessage(UserModel* sender, UserModel* receiver, QString message) const;
        void generateCertificate() const;
};


#endif //RSACONTROLLER_H
