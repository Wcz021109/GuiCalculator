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
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow() override;

private:
    CalculateCore* core;
    DualDisplayPanel* dualDisplayPanel;
    BasicInputPanel* basicInputPanel;

    QVBoxLayout VLay;

    void iniUi();

    void iniSettings();
    void iniRouteSignalSlots();

private slots:
    //来自计算核心
    void do_calculateCompleted(const QString &result);
    void do_coreErrorOccured(const ErrorCode &errorCode, const QString &error);

    //来自基本按键模块
    void receive_btnsInputClicked(const InputUnit &input);
    void receive_btnsOprClicked(const OprUnit &opr);
    void receive_btnsMemClicked(const MemOprUnit &memOpr);

    //回环槽
    void do_deleteFromInput();
    void do_clearInput();

signals:
    //至计算核心
    void calculate(const QList<InputUnit> &formula);

    //至双行显示

    //回环信号
    void deleteFromInput();
    void clearInput();

};


#endif //GUICALCULATOR_MAINWINDOW_H