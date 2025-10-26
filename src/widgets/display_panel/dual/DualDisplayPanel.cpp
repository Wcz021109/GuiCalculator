#include "DualDisplayPanel.h"

DualDisplayPanel::DualDisplayPanel(QWidget *parent) :
        QWidget(parent),
        lblFormula(nullptr),
        lblAns(nullptr),
        VLay(nullptr)
{
    iniUI();
}

DualDisplayPanel::~DualDisplayPanel() = default;

void DualDisplayPanel::iniUI() {
    lblFormula=new QLabel(this);
    lblFormula->setText("");
    lblFormula->setFont(QFont("Arial", 12));
    lblFormula->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    lblFormula->setFixedSize(QSize(200, 20));

    lblAns=new QLabel(this);
    lblAns->setText("");
    lblAns->setFont(QFont("Arial", 30));
    lblAns->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    lblAns->setMinimumSize(QSize(200, 50));

    VLay = new QVBoxLayout(this);
    VLay->addWidget(lblFormula);
    VLay->addWidget(lblAns);

    setLayout(VLay);
}

void DualDisplayPanel::displayFormula(const QList<InputUnit> &formula) const {
    QString display;
    for (const InputUnit &input : formula) {
        display.append(input.keyName);
    }
    lblFormula->setText(display);
}

void DualDisplayPanel::displayAnswer(const qreal &result) const{
    lblAns->setStyleSheet("color: blue");
    lblAns->setText(QString::number(result));
}

void DualDisplayPanel::displayError(const ErrorCode &code) const {
    lblAns->setStyleSheet("color: red");
    switch (code) {
        case ErrorCode::Domain_error: lblAns->setText("Math Error"); break;
        case ErrorCode::Invalid_argument: lblAns->setText("Syntax Error"); break;
        case ErrorCode::Stack_error: lblAns->setText("Stack Error"); break;
        case ErrorCode::Other: lblAns->setText("Unknown Error"); break;
        default: lblAns->setText("Critical error detected"); break;
    };
}