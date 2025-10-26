#include "mainwindow.h"

Mainwindow::Mainwindow(QMainWindow *parent) :
        QMainWindow(parent),
        mainWidget(nullptr),
        core(nullptr),
        VLay(nullptr),
        dualDisplayPanel(nullptr),
        basicInputPanel(nullptr)
{
    core = new CalculateCore(this);
    iniUi();
    iniSignalSlots();
}

Mainwindow::~Mainwindow() = default;

void Mainwindow::iniUi() {
    QWidget* mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    dualDisplayPanel = new DualDisplayPanel(this);
    basicInputPanel = new BasicInputPanel(this);

    VLay = new QVBoxLayout(mainWidget);
    VLay->addWidget(dualDisplayPanel);
    VLay->addWidget(basicInputPanel);
}

void Mainwindow::receive_btnsOprClicked(const OprUnit &oprUnit) {
    switch (oprUnit.opr) {
        case OprType::Clear: emit clearInput(); break;
        case OprType::Delete: emit deleteFromInput(); break;
        case OprType::Calculate: emit calculate();break;
        default: break;
    }
}

void Mainwindow::iniSignalSlots() {
    connect(basicInputPanel, &BasicInputPanel::btnsInputClicked, core, &CalculateCore::appendToFormula);
    connect(basicInputPanel, &BasicInputPanel::btnsOprClicked, this, &Mainwindow::receive_btnsOprClicked);
    //connect(basicInputPanel, &BasicInputPanel::btnsMemClicked, this, &Mainwindow::receive_btnsMemClicked);

    connect(this,&Mainwindow::deleteFromInput,core,&CalculateCore::deleteFromFormula);
    connect(this,&Mainwindow::clearInput,core,&CalculateCore::clearFormula);
    connect(this,&Mainwindow::calculate,core,&CalculateCore::do_calculate);

    connect(core,&CalculateCore::formulaChanged,dualDisplayPanel,&DualDisplayPanel::displayFormula);

    connect(core,&CalculateCore::calculateCompleted,dualDisplayPanel,&DualDisplayPanel::displayAnswer);
    connect(core, &CalculateCore::errorOccurred,dualDisplayPanel,&DualDisplayPanel::displayError);
}