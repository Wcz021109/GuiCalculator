#include "mainwindow.h"
#include "ui_Mainwindow.h"


Mainwindow::Mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::Mainwindow) {
    ui->setupUi(this);
}

Mainwindow::~Mainwindow() {
    delete ui;
}