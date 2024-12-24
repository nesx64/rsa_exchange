
#ifndef PUBLICKEYMODEL_H
#define PUBLICKEYMODEL_H

#include "KeyModel.h"

class PublicKeyModel : public KeyModel {
    public:
        PublicKeyModel(UserModel* u, cpp_int e);
        explicit PublicKeyModel(UserModel* u);
        ~PublicKeyModel();
};

#endif //PUBLICKEYMODEL_H
