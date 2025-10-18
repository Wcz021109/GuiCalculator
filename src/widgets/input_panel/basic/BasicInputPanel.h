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
    void iniGroup();
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
    QPushButton *btnNumPercent;
    QPushButton *btnNumTNegative;

    QPushButton *btnSigPlus;
    QPushButton *btnSigMinus;
    QPushButton *btnSigMultiply;
    QPushButton *btnSigDivide;
    QPushButton *btnSigPower;
    QPushButton *btnSigParentLeft;
    QPushButton *btnSigParentRight;

    QPushButton *btnFunctionRandom;
    QPushButton *btnFunctionReciprocal;
    QPushButton *btnFunctionSci;
    QPushButton *btnFunctionSqr;
    QPushButton *btnFunctionSqrt;

    QPushButton *btnConstAns;
    QPushButton *btnConstExp;
    QPushButton *btnConstPi;

    QPushButton *btnOperClear;
    QPushButton *btnOprDelete;
    QPushButton *btnOprEqual;

    QVector<QPushButton *> btnNumberList;
    QVector<QPushButton *> btnSignList;
    QVector<QPushButton *> btnFunctionList;
    QVector<QPushButton *> btnConstList;
    QVector<QPushButton *> btnOperationList;

signals:
    void btnNumberSignClicked();
    void btnConstClicked();
    void btnFunctionClicked();
    void bthOperationClicked();

};


#endif //GUICALCULATOR_BASICINPUTPANEL_H