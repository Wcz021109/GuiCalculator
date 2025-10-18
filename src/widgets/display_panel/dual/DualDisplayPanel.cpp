#include "DualDisplayPanel.h"

#include <QBoxLayout.h>
#include <QFile>
#include <QTextStream>

DualDisplayPanel::DualDisplayPanel(QWidget *parent) :
        QWidget(parent),
        lblPreviousDisplay(nullptr),
        lblCurrentDisplay(nullptr),
        VLay(nullptr)
{
    iniUI();
    iniSignalSlots();
}

DualDisplayPanel::~DualDisplayPanel() = default;

void DualDisplayPanel::iniUI() {
    lblCurrentDisplay=new QLabel(this);
    lblCurrentDisplay->setText("");
    lblCurrentDisplay->setFont(QFont("Arial", 30));
    lblCurrentDisplay->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    lblCurrentDisplay->setMinimumSize(QSize(200, 50));

    lblPreviousDisplay=new QLabel(this);
    lblPreviousDisplay->setText("");
    lblPreviousDisplay->setFont(QFont("Arial", 12));
    lblPreviousDisplay->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    lblPreviousDisplay->setStyleSheet("color: gray;");
    lblPreviousDisplay->setFixedSize(QSize(200, 20));

    VLay = new QVBoxLayout(this);
    VLay->addWidget(lblPreviousDisplay);
    VLay->addWidget(lblCurrentDisplay);
    setLayout(VLay);
}

QString DualDisplayPanel::CurrentFormula() const {
    return lblCurrentDisplay->text();
}

QString DualDisplayPanel::PreviousFormula() const {
    return lblPreviousDisplay->text();
}

void DualDisplayPanel::setDisplay(const QString &formula) {
    lblCurrentDisplay->setText(formula);
    emit displayChanged();
}

void DualDisplayPanel::appendToDisplay(const QString &str){
    QString currentDisplay = lblCurrentDisplay->text();
    currentDisplay += str;
    lblPreviousDisplay->setText(currentDisplay);
    emit displayChanged();
}

void DualDisplayPanel::chopFromDisplay() {
    QString currentDisplay = lblCurrentDisplay->text();
    currentDisplay.chop(1);
    lblPreviousDisplay->setText(currentDisplay);
    emit displayChanged();
}

void DualDisplayPanel::clearCurrentDisplay(){
    lblCurrentDisplay->clear();
    emit displayChanged();
}

void DualDisplayPanel::clearAllDisplay(){
    lblCurrentDisplay->clear();
    lblPreviousDisplay->clear();
    emit displayChanged();
}

void DualDisplayPanel::displayResult(const QString &result){
    QString formula = QString("%1 = %2")
    .arg(lblCurrentDisplay->text())
    .arg(result);
    lblPreviousDisplay->setStyleSheet("color: gray;");
    lblPreviousDisplay->setText(lblCurrentDisplay->text());
    lblCurrentDisplay->setText(result);
    emit displayChanged();

    QFile file("history.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream write(&file);
        write << formula <<Qt::endl;
    }
}

void DualDisplayPanel::displayError(const QString &errorCode){
    lblPreviousDisplay->setStyleSheet("color: red;");
    lblPreviousDisplay->setText(errorCode);
}

void DualDisplayPanel::iniSignalSlots(){}