#include "DualDisplayPanel.h"

DualDisplayPanel::DualDisplayPanel(QWidget *parent) :
        QWidget(parent),
        lblPreviousDisplay(nullptr),
        lblCurrentDisplay(nullptr),
        VLay(nullptr)
{
    iniUI();
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

void DualDisplayPanel::setCurrentDisplay(const QString &display) const{
    lblCurrentDisplay->setText(display);
}

void DualDisplayPanel::setPreviousDisplay(const QString &display) const{
    lblPreviousDisplay->setText(display);
}