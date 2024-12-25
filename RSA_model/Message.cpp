#include "Message.h"

#include "../RSA_controller/Generator.hpp"

Message::Message(UserModel* s, QString b) {
    this->sender = s;
    this->body = &b;
    this->hash = Generator::getGenerator()->hash(b, s->getN());
}
