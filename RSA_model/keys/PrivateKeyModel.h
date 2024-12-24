#ifndef PRIVATEKEYMODEL_H
#define PRIVATEKEYMODEL_H

#include "KeyModel.h"

class PrivateKeyModel : public KeyModel{
    public:
        PrivateKeyModel(UserModel* u, cpp_int v);
        explicit PrivateKeyModel(UserModel* u);
        ~PrivateKeyModel();
};

#endif //PRIVATEKEYMODEL_H
