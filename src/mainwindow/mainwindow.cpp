#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
        QMainWindow(parent),
        core(nullptr),
        dualDisplayPanel(nullptr),
        basicInputPanel(nullptr)
{
    iniUi();
}

Mainwindow::~Mainwindow() = default;

void Mainwindow::iniUi() {
    core = new CalculateCore(this);
    dualDisplayPanel = new DualDisplayPanel(this);
    basicInputPanel = new BasicInputPanel(this);
    iniRouteSignalSlots();
}

void Mainwindow::iniRouteSignalSlots() {
    connect(basicInputPanel, &BasicInputPanel::btnsInputClicked, core, &CalculateCore::appendToFormula);
    connect(basicInputPanel, &BasicInputPanel::btnsOprClicked, this, &Mainwindow::receive_btnsOprClicked);
    connect(basicInputPanel, &BasicInputPanel::btnsMemClicked, this, &Mainwindow::receive_btnsMemClicked);

    connect(this,&Mainwindow::deleteFromInput,this,&Mainwindow::do_deleteFromInput);
    connect(this,&Mainwindow::clearInput,this,&Mainwindow::do_clearInput);
}