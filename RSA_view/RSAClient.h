#ifndef RSACLIENT_H
#define RSACLIENT_H

#include <QMainWindow>
#include <QWindow>

#include "../RSA_model/UserModel.h"

class RSAClient : QWindow {
private:
    QMainWindow* parent;
    UserModel* user;
};



#endif //RSACLIENT_H
