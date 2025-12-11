#ifndef GUICALCULATOR_MAINWINDOW_H
#define GUICALCULATOR_MAINWINDOW_H

#include "CalculateCore.h"
#include "DualDisplayPanel.h"
#include "BasicInputPanel.h"

#include "unit.h"
#include "error.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow() override;

private:
    CalculateCore* core;
    DualDisplayPanel* dualDisplayPanel;
    BasicInputPanel* basicInputPanel;

    QWidget* mainWidget;
    QVBoxLayout* VLay;

    void iniUi();
    void iniSignalSlots();
    //void iniSettings();

};


#endif //GUICALCULATOR_MAINWINDOW_H