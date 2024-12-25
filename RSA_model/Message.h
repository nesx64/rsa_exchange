#ifndef MESSAGE_H
#define MESSAGE_H

#include <boost/multiprecision/cpp_int.hpp>

class QString;
using boost::multiprecision::cpp_int;

class UserModel;

class Message {
    UserModel* sender;
    QString* body;
    cpp_int hash;
public:
    Message(UserModel* s, QString b);
    ~Message() = default;
};

#endif //MESSAGE_H
