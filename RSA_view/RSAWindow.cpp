#include "RSAWindow.hpp"

RSAWindow::RSAWindow(QWidget *parent, const QString& title, RSAController* ct, RSAModel* md) : QMainWindow(parent){
    setWindowTitle(title);
    resize(800,600);
    this->title = new QLabel(title, this);
    this->controller = ct;
    this->model = md;
}

RSAWindow::~RSAWindow() {}

