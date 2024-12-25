#include "RSAWindow.hpp"

#include <QPushButton>
#include "ui_dev_rsa-ex.h"
#include <QDesktopServices>
#include <QUrl>

RSAWindow::RSAWindow(QWidget *parent, const QString& title, RSAController* ct, RSAModel* md) : QMainWindow(parent){
    setWindowTitle(title);
    resize(800,600);

    ui = new Ui::RSAWindow;
    ui->setupUi(this);

    this->title = new QLabel(title, this);
    this->controller = ct;
    this->model = md;

    connect(ui->tempOpenGithubButton, &QPushButton::clicked, this, [this] {
        QDesktopServices::openUrl(QUrl("https://github.com/nesx64/rsa_exchange"));
    });
}

RSAWindow::~RSAWindow() = default;

