#include "BasicInputPanel.h"

BasicInputPanel::BasicInputPanel(QWidget *parent) :
        QWidget(parent),
        GLay(nullptr),
        btnNum0(nullptr),
        btnNum1(nullptr),
        btnNum2(nullptr),
        btnNum3(nullptr),
        btnNum4(nullptr),
        btnNum5(nullptr),
        btnNum6(nullptr),
        btnNum7(nullptr),
        btnNum8(nullptr),
        btnNum9(nullptr),
        btnNumDecimal(nullptr),
        btnNumPercent(nullptr),
        btnNumTNegative(nullptr),
        btnSigPlus(nullptr),
        btnSigMinus(nullptr),
        btnSigMultiply(nullptr),
        btnSigDivide(nullptr),
        btnSigPower(nullptr),
        btnSigParentLeft(nullptr),
        btnSigParentRight(nullptr),
        btnFunctionRandom(nullptr),
        btnFunctionReciprocal(nullptr),
        btnFunctionSci(nullptr),
        btnFunctionSqr(nullptr),
        btnFunctionSqrt(nullptr),
        btnConstAns(nullptr),
        btnConstExp(nullptr),
        btnConstPi(nullptr),
        btnOperClear(nullptr),
        btnOprDelete(nullptr),
        btnOprEqual(nullptr)
{
    iniUi();
}

BasicInputPanel::~BasicInputPanel() = default;

void BasicInputPanel::iniGroup() {
    btnNumberList.append(btnNum0);
    btnNumberList.append(btnNum1);
    btnNumberList.append(btnNum2);
    btnNumberList.append(btnNum3);
    btnNumberList.append(btnNum4);
    btnNumberList.append(btnNum5);
    btnNumberList.append(btnNum6);
    btnNumberList.append(btnNum7);
    btnNumberList.append(btnNum8);
    btnNumberList.append(btnNum9);

    btnSignList.append(btnSigPlus);
    btnSignList.append(btnSigMinus);
    btnSignList.append(btnSigMultiply);
    btnSignList.append(btnSigDivide);
    btnSignList.append(btnSigPower);
    btnSignList.append(btnSigParentLeft);
    btnSignList.append(btnSigParentRight);

    btnFunctionList.append(btnFunctionRandom);
    btnFunctionList.append(btnFunctionReciprocal);
    btnFunctionList.append(btnFunctionSci);
    btnFunctionList.append(btnFunctionSqr);
    btnFunctionList.append(btnFunctionSqrt);
}

void BasicInputPanel::iniUi() {
    btnNum0 = new QPushButton("0");
    btnNum1 = new QPushButton("1");
    btnNum2 = new QPushButton("2");
    btnNum3 = new QPushButton("3");
    btnNum4 = new QPushButton("4");
    btnNum5 = new QPushButton("5");
    btnNum6 = new QPushButton("6");
    btnNum7 = new QPushButton("7");
    btnNum8 = new QPushButton("8");
    btnNum9 = new QPushButton("9");
    btnNumDecimal = new QPushButton("10");
    btnNumPercent = new QPushButton("11");
    btnNumTNegative = new QPushButton("(-)");

    btnSigPlus = new QPushButton("＋");
    btnSigMinus = new QPushButton("－");
    btnSigMultiply = new QPushButton("×");
    btnSigDivide = new QPushButton("÷");
    btnSigPower = new QPushButton("xⁿ");
    btnSigParentLeft = new QPushButton("(");
    btnSigParentRight = new QPushButton(")");

    btnFunctionRandom = new QPushButton("Ran#");
    btnFunctionReciprocal = new QPushButton("⅟");
    btnFunctionSqr = new QPushButton("x²");
    btnFunctionSqrt = new QPushButton("√x");

    btnConstAns = new QPushButton("Ans");
    btnConstExp = new QPushButton("e");
    btnConstPi = new QPushButton("π");

    btnOperClear = new QPushButton("AC");
    btnOprDelete = new QPushButton("←");
    btnOprEqual = new QPushButton("＝");

    QGridLayout *GLay = new QGridLayout(this);
    GLay->setSpacing(3);
    GLay->setContentsMargins(5,5,5,5);

    GLay->addWidget(btnFunctionSci,0,0);
    GLay->addWidget(btnFunctionReciprocal, 0, 1);
    GLay->addWidget(btnFunctionSqr, 0, 2);
    GLay->addWidget(btnFunctionSqrt, 0, 3);
    GLay->addWidget(btnSigPower, 0, 4);

    GLay->addWidget(btnConstAns, 1, 0);
    GLay->addWidget(btnNumTNegative, 1, 1);
    GLay->addWidget(btnNumPercent, 1, 2);
    GLay->addWidget(btnConstPi, 1, 3);
    GLay->addWidget(btnConstExp, 1, 4);

    GLay->addWidget(btnNum7, 2,0);
    GLay->addWidget(btnNum8, 2,1);
    GLay->addWidget(btnNum9, 2,2);
    GLay->addWidget(btnSigParentLeft, 2,3);
    GLay->addWidget(btnSigParentRight, 2, 4);

    GLay->addWidget(btnNum4,3,0);
    GLay->addWidget(btnNum5, 3,1);
    GLay->addWidget(btnNum6, 3,2);
    GLay->addWidget(btnSigMultiply, 3, 3);
    GLay->addWidget(btnSigDivide, 3, 4);

    GLay->addWidget(btnNum1,4,0);
    GLay->addWidget(btnNum2,4,1);
    GLay->addWidget(btnNum3,4,2);
    GLay->addWidget(btnSigPlus, 4,3);
    GLay->addWidget(btnSigMinus, 4,4);

    GLay->addWidget(btnNum0,5,0);
    GLay->addWidget(btnNumDecimal, 5,1);
    GLay->addWidget(btnOperClear, 5,2);
    GLay->addWidget(btnOprDelete, 5,3);
    GLay->addWidget(btnOprEqual, 5,4);

    setLayout(GLay);
}