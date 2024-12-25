#include <QApplication>
#include <QLabel>

#include "RSA_controller/Generator.hpp"
#include "RSA_controller/RSAController.h"
#include "RSA_model/RSAModel.h"
#include "RSA_model/UserModel.h"
#include "RSA_view/RSAWindow.hpp"

int main(int argc, char * argv[]) {

 QMap<QString, UserModel*> users;

 users.insert("Bob", new UserModel("Bob"));
 Generator::getGenerator()->generateKeysFor(users["Bob"]);
 users.insert("Alice", new UserModel("Alice"));
 Generator::getGenerator()->generateKeysFor(users["Alice"]);

 users.insert("CA", new CAModel("CA"));

 RSAModel* model = new RSAModel(users);
 RSAController* controller = new RSAController(model);
 controller->generateCertificate();

 QApplication app(argc,argv);
 RSAWindow window(nullptr,QString("rsa_ex"), controller, model);
 window.show();

 return app.exec();
}
