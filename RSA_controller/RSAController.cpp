#include "RSAController.h"
#include "Generator.hpp"

const std::string RSAController::MESSAGE_SEPARATOR = "::";

RSAController::RSAController() = default;
RSAController::~RSAController() = default;

RSAController::RSAController(RSAModel* m) {
    model = m;
    Generator::getGenerator()->generateKeysFor(model->getUser("CA"));
}

void RSAController::setKeysFor(UserModel* u) const {
    Generator::getGenerator()->generateKeysFor(u);
    if (Generator::getGenerator()->testKeys(u, u->getPhi())) {
        std::cout << "Test for keys was a success" << std::endl;
    } else {
        std::cout << "Test for keys was a failure" << std::endl;
        u->removeKeys();
    }
}

void RSAController::sendMessage(UserModel *sender, UserModel *receiver, QString message) const {
    cpp_int hashMessage = Generator::getGenerator()->hash(message,sender->getN());

    QByteArray messageBytes = message.toUtf8();
    cpp_int temp = 0;
    for (int i = 0; i < messageBytes.size(); i++) {
        temp = (temp << 8) | static_cast<unsigned char>(messageBytes[i]);
    }

    cpp_int encryptedMessage = Generator::getGenerator()->modularPow(temp,receiver->getPublicKey()->getValue(), receiver->getN());
    QString fullMessage = QString::fromStdString(to_string(encryptedMessage)) +
                     QString::fromStdString(MESSAGE_SEPARATOR) +
                     QString::fromStdString(Generator::getGenerator()->signMessage(hashMessage, sender->getPrivateKey(), sender->getN()).str());
    QString* parts = fullMessage.split(QString::fromStdString(MESSAGE_SEPARATOR)).data();
    if (parts->size() != 2) {
        return;
    }
    cpp_int receivedEncryptedMessage(parts[0].toStdString());
    cpp_int receivedSignture(parts[1].toStdString());

    QString decrypted((Generator::getGenerator()->modularPow(receivedEncryptedMessage, receiver->getPrivateKey()->getValue(), receiver->getN()).str().data()));

    CAModel* ca = static_cast<CAModel*>(model->getUser("CA"));
    Certificate senderCertif = ca->getCertificateOf(sender);
    if (!ca->verifyCertificate(senderCertif)) {
        std::cout << "The authenticity of the sender couldn't be proved." << std::endl;
        return;
    }
    std::cout << "The authenticity was proved by the CA." << std::endl;
    cpp_int calculatedHash = Generator::getGenerator()->hash(decrypted, sender->getN());
    if (Generator::getGenerator()->checkSign(receivedSignture, calculatedHash, sender->getPublicKey(), sender->getN())) {
        std::cout << "The signature of the received message is valid." << std::endl;
    } else {
        std::cout << "The integrity of the message was compromised." << std::endl;
    }
}

void RSAController::generateCertificate() const {
    UserModel* alice = model->getUser("Alice");
    UserModel* bob = model->getUser("Bob");
    CAModel* ca = static_cast<CAModel*>(model->getUser("CA"));

    Certificate aliceC = gatherDataForCertificate(alice, ca);
    Certificate bobC = gatherDataForCertificate(bob, ca);

    ca->addCertificate(aliceC);
    ca->addCertificate(bobC);
    std::cout << "Certificates for Bob & Alice was successfully added to CA list." << std::endl;
}

Certificate RSAController::gatherDataForCertificate(UserModel *u, CAModel *ca) const {
    cpp_int hashPubKey = Generator::getGenerator()->hash(u->getPublicKey()->getValue().str().data(), ca->getN());
    cpp_int sign = Generator::getGenerator()->signMessage(hashPubKey,ca->getPrivateKey(), ca->getN());
    return Certificate(u,sign);
}




