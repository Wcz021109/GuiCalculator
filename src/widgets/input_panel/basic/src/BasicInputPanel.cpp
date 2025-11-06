#include "BasicInputPanel.h"
#include "unit.h"

BasicInputPanel::BasicInputPanel(QWidget *parent) :
        QWidget(parent),
        HLay(nullptr),
        btnMemClear(nullptr),
        btnMemRcl(nullptr),
        btnMemStore(nullptr),
        btnMemAdd(nullptr),
        btnMemSub(nullptr),
        GLay(nullptr),
        btnNum{nullptr},
        btnNumDecimal(nullptr),
        btnNumNegative(nullptr),
        btnSufPercent(nullptr),
        btnSufSqr(nullptr),
        btnSigPlus(nullptr),
        btnSigMinus(nullptr),
        btnSigMultiply(nullptr),
        btnSigDivide(nullptr),
        btnSigSci(nullptr),
        btnSigPower(nullptr),
        btnSigParentLeft(nullptr),
        btnSigParentRight(nullptr),
        btnFuncRecp(nullptr),
        btnFuncSqrt(nullptr),
        btnMemAns(nullptr),
        btnConstExp(nullptr),
        btnConstPi(nullptr),
        btnConstRandom(nullptr),
        btnOprClear(nullptr),
        btnOprDelete(nullptr),
        btnOprEqual(nullptr),
        VLay(nullptr)
{
    iniInputButtons();
    iniOprButtons();
    iniMemButtons();
    iniLayout();
    iniSender();
}

BasicInputPanel::~BasicInputPanel() = default;

void BasicInputPanel::iniInputButtons() {
    for (int i = 0; i<10;i++) {
        btnNum[i] = new InputButton(
            InputUnit(QString::number(i), InputType::Digit),this);
        btnsInput.append(btnNum[i]);
    }
    btnNumDecimal = new InputButton(
        InputUnit(".",InputType::Digit));
    btnsInput.append(btnNumDecimal);
    btnNumNegative = new InputButton("(-)",
        InputUnit("-","-",InputType::Digit),this);
    btnsInput.append(btnNumNegative);

    btnSufPercent = new InputButton(
        InputUnit("%",InputType::Suffix),this);
    btnsInput.append(btnSufPercent);
    btnSufSqr = new InputButton("x²",
        InputUnit("²","^2",InputType::Suffix),this);
    btnsInput.append(btnSufSqr);

    btnSigPlus = new InputButton(
        InputUnit("+","+",InputType::Sign),this);
    btnsInput.append(btnSigPlus);
    btnSigMinus = new InputButton(
        InputUnit("-","-",InputType::Sign),this);
    btnsInput.append(btnSigMinus);
    btnSigMultiply = new InputButton(
        InputUnit("×","*",InputType::Sign),this);
    btnsInput.append(btnSigMultiply);
    btnSigDivide = new InputButton(
        InputUnit("÷","/",InputType::Sign),this);
    btnsInput.append(btnSigDivide);
    btnSigSci = new InputButton("×10ⁿ",
        InputUnit("×10^","S",InputType::Sign),this);
    btnsInput.append(btnSigSci);
    btnSigPower = new InputButton("xⁿ",
        InputUnit("^",InputType::Sign),this);
    btnsInput.append(btnSigPower);
    btnSigParentLeft = new InputButton(
        InputUnit("(",InputType::Sign),this);
    btnsInput.append(btnSigParentLeft);
    btnSigParentRight = new InputButton(
        InputUnit(")",InputType::Sign),this);
    btnsInput.append(btnSigParentRight);

    btnFuncRecp = new InputButton("⅟",
        InputUnit("1/(","recp(",InputType::Function),this);
    btnsInput.append(btnFuncRecp);
    btnFuncSqrt = new InputButton("√x",
        InputUnit("√(","sqrt(",InputType::Function),this);
    btnsInput.append(btnFuncSqrt);

    btnMemAns = new InputButton(
        InputUnit("Ans","R",InputType::Memory),this);
    btnsInput.append(btnMemAns);
    btnConstExp = new InputButton(
        InputUnit("e","EXP",InputType::Const),this);
    btnsInput.append(btnConstExp);
    btnConstPi = new InputButton(
        InputUnit("π","PI",InputType::Const),this);
    btnsInput.append(btnConstPi);
}
void BasicInputPanel::iniOprButtons() {
    btnOprClear = new OprButton("AC",
        OprUnit(OprType::Clear),this);
    btnsOperation.append(btnOprClear);
    btnOprDelete = new OprButton("←",
        OprUnit(OprType::Delete),this);
    btnsOperation.append(btnOprDelete);
    btnOprEqual = new OprButton("＝",
        OprUnit(OprType::Calculate),this);
    btnsOperation.append(btnOprEqual);
}

void BasicInputPanel::iniMemButtons() {
    btnMemClear = new MemButton("MC",
        MemOprUnit('M',MemOpr::Clear));
    btnsMemOpr.append(btnMemClear);
    btnMemRcl = new MemButton("MR",
        MemOprUnit('M',MemOpr::Read));
    btnsMemOpr.append(btnMemRcl);
    btnMemStore = new MemButton("MS",
        MemOprUnit('M',MemOpr::Store));
    btnsMemOpr.append(btnMemStore);
    btnMemAdd = new MemButton("M+",
        MemOprUnit('M',MemOpr::Add));
    btnsMemOpr.append(btnMemAdd);
    btnMemSub = new MemButton("M-",
        MemOprUnit('M',MemOpr::Substract));
    btnsMemOpr.append(btnMemSub);
}

void BasicInputPanel::iniLayout() {
    GLay = new QGridLayout();
    GLay->setSpacing(3);
    GLay->setContentsMargins(5,5,5,5);

    GLay->addWidget(btnSigSci,0,0);
    GLay->addWidget(btnFuncRecp, 0, 1);
    GLay->addWidget(btnSufSqr, 0, 2);
    GLay->addWidget(btnFuncSqrt, 0, 3);
    GLay->addWidget(btnSigPower, 0, 4);

    GLay->addWidget(btnMemAns, 1, 0);
    GLay->addWidget(btnNumNegative, 1, 1);
    GLay->addWidget(btnSufPercent, 1, 2);
    GLay->addWidget(btnConstPi, 1, 3);
    GLay->addWidget(btnConstExp, 1, 4);

    GLay->addWidget(btnNum[7], 2,0);
    GLay->addWidget(btnNum[8], 2,1);
    GLay->addWidget(btnNum[9], 2,2);
    GLay->addWidget(btnSigParentLeft, 2,3);
    GLay->addWidget(btnSigParentRight, 2, 4);

    GLay->addWidget(btnNum[4],3,0);
    GLay->addWidget(btnNum[5], 3,1);
    GLay->addWidget(btnNum[6], 3,2);
    GLay->addWidget(btnSigMultiply, 3, 3);
    GLay->addWidget(btnSigDivide, 3, 4);

    GLay->addWidget(btnNum[1],4,0);
    GLay->addWidget(btnNum[2],4,1);
    GLay->addWidget(btnNum[3],4,2);
    GLay->addWidget(btnSigPlus, 4,3);
    GLay->addWidget(btnSigMinus, 4,4);

    GLay->addWidget(btnNum[0],5,0);
    GLay->addWidget(btnNumDecimal, 5,1);
    GLay->addWidget(btnOprDelete, 5,2);
    GLay->addWidget(btnOprClear, 5,3);
    GLay->addWidget(btnOprEqual, 5,4);

    HLay = new QHBoxLayout();
    HLay->setSpacing(3);
    HLay->setContentsMargins(5,5,5,5);

    HLay->addWidget(btnMemClear);
    HLay->addWidget(btnMemRcl);
    HLay->addWidget(btnMemStore);
    HLay->addWidget(btnMemAdd);
    HLay->addWidget(btnMemSub);

    VLay = new QVBoxLayout(this);
    VLay->addLayout(HLay);
    VLay->addLayout(GLay);
    setLayout(VLay);
}

void BasicInputPanel::send_btnsInputClicked() {
    try {
        InputButton *clickedButton = qobject_cast<InputButton *>(QObject::sender());
        if (!clickedButton) {
            qCritical() << "BasicInputPanel::Not an input button!";
            return;
        }
        emit btnsInputClicked(clickedButton->getInputUnit());
    }catch (const std::exception &e) {
        qCritical() << "BasicInputPanel::Exception in send_btnsInputClicked: " << e.what();
    }catch (...) {
        qCritical() << "BasicInputPanel::Unknown exception in send_btnsInputClicked";
    }
}

void BasicInputPanel::send_btnsOprClicked() {
    try {
        OprButton *clickedButton = qobject_cast<OprButton *>(QObject::sender());
        if (!clickedButton) {
            qCritical() << "BasicInputPanel::Not an operate button!";
            return;
        }
        emit btnsOprClicked(clickedButton->getOprUnit());
    }catch (const std::exception &e) {
        qCritical() << "BasicInputPanel::Exception in send_btnsOprClicked: " << e.what();
    }catch (...) {
        qCritical() << "BasicInputPanel::Unknown exception send_btnsOprClicked";
    }
}

void BasicInputPanel::send_btnsMemClicked() {
    try {
        MemButton *clickedButton = qobject_cast<MemButton *>(QObject::sender());
        if (!clickedButton) {
            qCritical() << "BasicInputPanel::Not a memorize button!";
            return;
        }
        emit btnsMemClicked(clickedButton->getMemOprUnit());
    }catch (const std::exception &e) {
        qCritical() << "BasicInputPanel::Exception in send_btnsMemClicked: " << e.what();
    }catch (...) {
        qCritical() << "BasicInputPanel::Unknown exception send_btnsMemClicked";
    }
}

void BasicInputPanel::iniSender() {
    for (InputButton *btn : btnsInput) {
        connect(btn,SIGNAL(clicked()),this,SLOT(send_btnsInputClicked()));
    }
    for (OprButton *btn : btnsOperation) {
        connect(btn,SIGNAL(clicked()),this,SLOT(send_btnsOprClicked()));
    }
    for (MemButton *btn : btnsMemOpr) {
        connect(btn,SIGNAL(clicked()),this,SLOT(send_btnsMemClicked()));
    }
}