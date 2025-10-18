#include "mainwindow.h"
#include "CalculateCore.h"
#include "DualDisplayPanel.h"
#include "MemoryPanel.h"
#include "BasicInputPanel.h"

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

void Mainwindow::iniUi() {
    core = new CalculateCore(this);
    iniCalculateCoreSignalSlots();
    dualDisplayPanel = new DualDisplayPanel(this);
    iniDualDisplaySignalSlots();
    basicInputPanel = new BasicInputPanel(this);
    iniBasicInputSignalSlots();
    memoryPanel = new MemoryPanel(this);
    iniMemorySignalSlots();
}

void Mainwindow::iniCalculateCoreSignalSlots() {
    connect(this, &Mainwindow::calculate, core, &CalculateCore::do_calculate);
    connect(core, &CalculateCore::calculateCompleted, this ,&Mainwindow::do_calculateCompleted);
    connect(core ,&CalculateCore::errorOccurred, this ,&Mainwindow::do_coreErrorOccured);
}

