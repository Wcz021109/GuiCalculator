#ifndef GUICALCULATOR_BASICINPUTPANEL_H
#define GUICALCULATOR_BASICINPUTPANEL_H

#include "unit.h"
#include "button.h"
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
    void send_inputButtonsClicked();
    void send_oprButtonsClicked();
    void send_memOprsClicked();

signals:
    void inputButtonsClicked(InputUnit input);
    void oprButtonClicked(OprUnit opr);
    void memButtonClicked(MemOprUnit memopr);
};

#endif //GUICALCULATOR_BASICINPUTPANEL_H