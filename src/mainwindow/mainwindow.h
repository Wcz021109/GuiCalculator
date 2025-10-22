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

    QString m_formula;

private:
    CalculateCore* core;
    DualDisplayPanel* dualDisplayPanel;
    BasicInputPanel* basicInputPanel;

    QVBoxLayout VLay;

    QList<InputUnit> inputUnits;

    void iniUi();

    void iniCalculateCoreSignalSlots();
    void iniDualDisplaySignalSlots();
    void iniBasicInputSignalSlots();
    void iniSettings();
    void iniRouteSignalSlots();

private slots:
    //来自计算核心
    void do_calculateCompleted(QString result);
    void do_coreErrorOccured(ErrorCode errorCode,QString error);

    //来自基本按键模块
    void do_btnOnBasicInputPanelClicked(InputUnit &input);

    //回环槽
    void do_insertToInput(InputUnit input);
    void do_deleteFromInput();
    void do_clearInput();

signals:
    //至计算核心
    void calculate(QList<InputUnit> &formula);

    //至双行显示

    //回环信号
    void insertToInput(InputUnit input);
    void deleteFromInput();
    void clearInput();

};


#endif //GUICALCULATOR_MAINWINDOW_H