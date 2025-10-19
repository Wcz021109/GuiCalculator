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

private:
    void iniUi();
    //信号和槽由父对象统一管理

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
    QPushButton *btnNumPNegative;
    QPushButton *btnNumSPercent;
    QPushButton *btnNumSSqr;

    QPushButton *btnSigPlus;
    QPushButton *btnSigMinus;
    QPushButton *btnSigMultiply;
    QPushButton *btnSigDivide;
    QPushButton *btnSigSci;
    QPushButton *btnSigPower;
    QPushButton *btnSigParentLeft;
    QPushButton *btnSigParentRight;

    QPushButton *btnFuncRecp;
    QPushButton *btnFuncSqrt;

    QPushButton *btnConstAns;
    QPushButton *btnConstExp;
    QPushButton *btnConstPi;
    QPushButton *btnConstRandom;

    QPushButton *btnOperClear;
    QPushButton *btnOprDelete;
    QPushButton *btnOprEqual;

signals:
    void btnNumberClicked(QVariant btnName);
    void btnNumPNegativeClicked();
    void btnNumSPercentClicked();
    void btnNumSSqurClicked();
    void btnSigPlusClicked();
    void btnSigMinusClicked();
    void btnSigMultiplyClicked();
    void btnSigDivideClicked();
    void btnSigSciClicked();
    void btnSigPowerClicked();
    void btnSigParentLeftClicked();
    void btnSigParentRightClicked();
    void btnFuncRecpClicked();
    void btnFuncSqrtClicked();
    void btnConstAnsClicked();
    void btnConstExpClicked();
    void btnConstPiClicked();
    void btnConstRandomClicked();
    void btnOperClearClicked();
    void btnOperDeleteClicked();
    void btnOperEqualClicked();

};


#endif //GUICALCULATOR_BASICINPUTPANEL_H