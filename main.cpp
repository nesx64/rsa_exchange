#include<iostream>
#include <QApplication>
#include <QLabel>

#include "RSA_controller/RSAController.h"
#include "RSA_model/RSAModel.h"
#include "RSA_model/UserModel.h"

int main(int argc, char * argv[]) {

 QMap<QString, UserModel> users;
 users.insert("Bob", UserModel("Bob"));
 users.insert("Alice", UserModel("Alice"));
 users.insert("CA", CAModel("CA"));

 RSAModel model(users);
 RSAController controller(&model);
 controller.generateCertificate();

 QApplication app(argc,argv);
 QLabel label("Hello, RSA!");
 label.show();
 return app.exec();
}
