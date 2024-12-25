#ifndef RSAWINDOW_H
#define RSAWINDOW_H

#include <QLabel>

#include "../RSA_controller/RSAController.h"
#include "RSAClient.h"

namespace Ui {
    class RSAWindow;
}

class RSAWindow final : public QMainWindow {
    Q_OBJECT

    public:
        explicit RSAWindow(QWidget *parent = nullptr,
            const QString& title = "default_win",
            RSAController* ct = nullptr,
            RSAModel* md = nullptr);

        ~RSAWindow() override;

    private:
        QLabel* title;
        RSAController* controller;
        RSAModel* model;
        QSet<RSAClient*> clients;
        Ui::RSAWindow *ui;
};

#endif