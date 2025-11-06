#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent) :
        QMainWindow(parent),
        core(nullptr),
        mainWidget(nullptr),
        dualDisplayPanel(nullptr),
        basicInputPanel(nullptr),
        VLay(nullptr)
{
    core = new CalculateCore(this);
    iniUi();
    iniSignalSlots();
}

MainWindow::~MainWindow() = default;

void MainWindow::iniUi() {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    dualDisplayPanel = new DualDisplayPanel(mainWidget);
    basicInputPanel = new BasicInputPanel(mainWidget);

    VLay = new QVBoxLayout(mainWidget);
    VLay->addWidget(dualDisplayPanel);
    VLay->addWidget(basicInputPanel);
    mainWidget->setLayout(VLay);
}

void MainWindow::iniSignalSlots() {
    connect(basicInputPanel, &BasicInputPanel::btnsInputClicked, core, &CalculateCore::appendToFormula);
    connect(basicInputPanel, &BasicInputPanel::btnsOprClicked, core, &CalculateCore::performOpr);
    connect(basicInputPanel, &BasicInputPanel::btnsMemClicked, core, &CalculateCore::performMemOpr);

    connect(core,&CalculateCore::formulaChanged,dualDisplayPanel,&DualDisplayPanel::displayFormula);

    connect(core,&CalculateCore::calculateCompleted,dualDisplayPanel,&DualDisplayPanel::displayAnswer);
    connect(core, &CalculateCore::errorOccurred,dualDisplayPanel,&DualDisplayPanel::displayError);
}