#include "RSAModel.h"

RSAModel::RSAModel(const QMap<QString, UserModel>& us) {
    addUsers(us);
}

void RSAModel::addUser(UserModel u) {
    users.insert(u.getName(), u);
    emit userAdded(u.getName());
}

void RSAModel::addUsers(const QMap<QString, UserModel>& us) {
    QMapIterator<QString, UserModel> i(us);
    while (i.hasNext()) {
        i.next();
        users.insert(i.key().toStdString().data(), i.value());
    }
    emit usersUpdated();
}

std::set<UserModel> RSAModel::getUsers() const {
    std::set<UserModel> res;
    for (auto it = users.begin(); it != users.end(); ++it) {
        res.insert(it.value());
    }
    return res;
}

UserModel *RSAModel::getUser(const QString &name) {
    if (!users.contains(name)) return nullptr;
    auto it = users.find(name);
    return &(*it);
}