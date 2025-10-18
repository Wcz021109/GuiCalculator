#include "../core/mainwindow.h"


Mainwindow::Mainwindow(QWidget *parent) :
        QMainWindow(parent),
        core(nullptr),
        dualDisplayPanel(nullptr),
        memoryPanel(nullptr),
        basicInputPanel(nullptr)
{
        iniUi();
}

Mainwindow::~Mainwindow() = default;