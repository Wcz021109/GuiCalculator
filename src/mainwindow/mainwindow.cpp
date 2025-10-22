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
    iniCalculateCoreSignalSlots();
    dualDisplayPanel = new DualDisplayPanel(this);
    iniDualDisplaySignalSlots();
    basicInputPanel = new BasicInputPanel(this);
    iniBasicInputSignalSlots();
    iniRouteSignalSlots();
}

void Mainwindow::iniCalculateCoreSignalSlots() {
    connect(this, &Mainwindow::calculate, core, &CalculateCore::do_calculate);
    connect(core, &CalculateCore::calculateCompleted, this ,&Mainwindow::do_calculateCompleted);
    connect(core ,&CalculateCore::errorOccurred, this ,&Mainwindow::do_coreErrorOccured);
}

void Mainwindow::iniDualDisplaySignalSlots() {

}

void Mainwindow::iniRouteSignalSlots() {
    connect(this,&Mainwindow::insertToInput,this,&Mainwindow::do_insertToInput);
    connect(this,&Mainwindow::deleteFromInput,this,&Mainwindow::do_deleteFromInput);
    connect(this,&Mainwindow::clearInput,this,&Mainwindow::do_clearInput);
}