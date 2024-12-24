#ifndef RSAMODEL_H
#define RSAMODEL_H

#include "UserModel.h"
#include <unordered_map>
#include <qobject.h>
#include <set>
#include <QMap>

class RSAModel final : QObject {
    Q_OBJECT
    QMap<QString,UserModel*> users;
        //log & output --> cf qt for observables/modifiable
    public:
        explicit RSAModel(const QMap<QString, UserModel*>& us);
        void addUser(UserModel* u);
        void addUsers(const QMap<QString, UserModel*>& us);
        std::set<UserModel*> getUsers() const;

        UserModel* getUser(const QString &name);
        //log methods linked to view itself
    signals:
        void userAdded(const QString& name);
        void usersUpdated();
};



#endif //RSAMODEL_H
