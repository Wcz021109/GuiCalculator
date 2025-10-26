#ifndef GUICALCULATOR_BASICINPUTPANEL_H
#define GUICALCULATOR_BASICINPUTPANEL_H

#include "unit.h"
#include "../button/button.h"
#include <QWidget>
#include <QGridLayout>

class BasicInputPanel : public QWidget {
    Q_OBJECT

public:
    explicit BasicInputPanel(QWidget *parent = nullptr);
    ~BasicInputPanel() override;

private:
    void iniInputButtons();
    void iniOprButtons();
    void iniLayout();
    void iniSender();

    QGridLayout *GLay;
    
    InputButton *btnNum[10];
    InputButton *btnNumDecimal;
    InputButton *btnNumNegative;

    InputButton *btnSufPercent;
    InputButton *btnSufSqr;

    InputButton *btnSigPlus;
    InputButton *btnSigMinus;
    InputButton *btnSigMultiply;
    InputButton *btnSigDivide;
    InputButton *btnSigSci;
    InputButton *btnSigPower;
    InputButton *btnSigParentLeft;
    InputButton *btnSigParentRight;

    InputButton *btnFuncRecp;
    InputButton *btnFuncSqrt;

    InputButton *btnConstAns;
    InputButton *btnConstExp;
    InputButton *btnConstPi;
    InputButton *btnConstRandom;

    OprButton *btnOprClear;
    OprButton *btnOprDelete;
    OprButton *btnOprEqual;

    QVector<InputButton *> btnsInput;
    QVector<OprButton *> btnsOperation;
    QVector<MemButton *> btnsMemOpr;

private slots:
    void send_btnsInputClicked();
    void send_btnsOprClicked();
    void send_btnsMemClicked();

signals:
    void btnsInputClicked(const InputUnit &input);
    void btnsOprClicked(const OprUnit &opr);
    void btnsMemClicked(const MemOprUnit &memOpr);
};

#endif //GUICALCULATOR_BASICINPUTPANEL_H