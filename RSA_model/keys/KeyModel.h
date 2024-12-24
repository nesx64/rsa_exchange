#ifndef KEYMODEL_H
#define KEYMODEL_H

#include "../UserModel.h"

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class KeyModel {
    protected:
      UserModel* user;
      cpp_int value;
    public:
        KeyModel();
        UserModel* getUser();
        cpp_int getValue();
        void setValue(cpp_int v);
        virtual ~KeyModel();
};

#endif //KEYMODEL_H
