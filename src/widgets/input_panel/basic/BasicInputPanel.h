#ifndef GUICALCULATOR_BASICINPUTPANEL_H
#define GUICALCULATOR_BASICINPUTPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class BasicInputPanel : private QWidget {
    Q_OBJECT

public:
    explicit BasicInputPanel(QWidget *parent = nullptr);
    ~BasicInputPanel() override;

public slots:

private:

    void iniUi();
    void iniSignalSlots();

signals:
    void do_btnNumberSignPressed();
    void do_btnConstPressed();
    void do_btnFunctionPressed();

    void do_bthOperationClicked();

private:
    QGridLayout *GLay;
    
    QPushButton *btnNum0;
    QPushButton *btnNum1;
    QPushButton *btnNum2;
    QPushButton *btnNum3;
    QPushButton *btnNum4;
    QPushButton *btnNum5;
    QPushButton *btnNum6;
    QPushButton *btnNum7;
    QPushButton *btnNum8;
    QPushButton *btnNum9;
    QPushButton *btnNumDecimal;
    QPushButton *btnNumPercent;

    QPushButton *btnSigPlus;
    QPushButton *btnSigMinus;
    QPushButton *btnSigMultiply;
    QPushButton *btnSigDivide;
    QPushButton *btnSigPower;
    QPushButton *btnSigParentLeft;
    QPushButton *btnSigParentRight;

    QPushButton *btnFunctionSci;
    QPushButton *btnFunctionSqr;
    QPushButton *btnFunctionSqrt;
    QPushButton *btnFunctionRandom;

    QPushButton *btnConstAns;
    QPushButton *btnConstPi;
    QPushButton *btnConstExp;

    QPushButton *btnOperClear;
    QPushButton *btnOprDelete;
    QPushButton *btnOprEqual;
};


#endif //GUICALCULATOR_BASICINPUTPANEL_H