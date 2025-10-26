#ifndef GUICALCULATOR_MAINWINDOW_H
#define GUICALCULATOR_MAINWINDOW_H

#include "CalculateCore.h"
#include "DualDisplayPanel.h"
#include "BasicInputPanel.h"

#include "unit.h"
#include "errorCode.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>

class Mainwindow : public QMainWindow {
    Q_OBJECT

public:
    explicit Mainwindow(QMainWindow *parent = nullptr);
    ~Mainwindow() override;

private:
    CalculateCore* core;
    DualDisplayPanel* dualDisplayPanel;
    BasicInputPanel* basicInputPanel;

    QWidget* mainWidget;
    QVBoxLayout* VLay;

    void iniUi();
    void iniSignalSlots();
    //void iniSettings();

private slots:
    //来自基本按键模块
    void receive_btnsOprClicked(const OprUnit &opr);
    //void receive_btnsMemClicked(const MemOprUnit &memOpr);

signals:
    void calculate();
    void deleteFromInput();
    void clearInput();

};


#endif //GUICALCULATOR_MAINWINDOW_H