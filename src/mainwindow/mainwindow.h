#ifndef GUICALCULATOR_MAINWINDOW_H
#define GUICALCULATOR_MAINWINDOW_H

#include "iniEnumStruct.h"
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

    QString m_formula;

private:
    CalculateCore* core;
    DualDisplayPanel* dualDisplayPanel;
    BasicInputPanel* basicInputPanel;
    MemoryPanel* memoryPanel;

    QVBoxLayout VLay;

    QList<InputUnit> inputUnits;

    void iniUi();

    void iniCalculateCoreSignalSlots();
    void iniDualDisplaySignalSlots();
    void iniBasicInputSignalSlots();
    void iniMemorySignalSlots();
    void iniSettings();
    void iniRouteSignalSlots();

private slots:
    void do_calculateCompleted(QString result);
    void do_coreErrorOccured(ErrorCode errorCode,QString error);

    void do_formulaRecording();

signals:
    void calculate(QList<InputUnit> &formula);
    
};


#endif //GUICALCULATOR_MAINWINDOW_H