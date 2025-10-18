#include "mainwindow.h"


Mainwindow::Mainwindow(QWidget *parent) :
        QMainWindow(parent),
        core(nullptr),
        dualDisplayPanel(nullptr),
        basicInputPanel(nullptr),
        memoryPanel(nullptr)
{
        iniUi();
}

Mainwindow::~Mainwindow() = default;