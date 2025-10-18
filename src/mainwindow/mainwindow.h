#ifndef GUICALCULATOR_MAINWINDOW_H
#define GUICALCULATOR_MAINWINDOW_H

#include "CalculateCore.h"
#include "DualDisplayPanel.h"
#include "MemoryPanel.h"
#include "BasicInputPanel.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>

class Mainwindow : public QMainWindow {
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow() override;

private:
    CalculateCore core;
    DualDisplayPanel dualDisplayPanel;
    MemoryPanel memoryPanel;
    BasicInputPanel basicInputPanel;

    void iniUi();
    void iniCalculateCoreSignalSlots();
    void iniDualDisplaySignalSlots();
    void iniBasicInputSignalSlots();
    void iniMemorySignalSlots();
    void iniSettings();

private slots:
    
};


#endif //GUICALCULATOR_MAINWINDOW_H