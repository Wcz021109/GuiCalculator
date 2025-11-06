#ifndef GUICALCULATOR_DISPLAY_H
#define GUICALCULATOR_DISPLAY_H

#include "unit.h"
#include "errorCode.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DualDisplayPanel : public QWidget{
    Q_OBJECT

public:
    explicit DualDisplayPanel(QWidget *parent);
    ~DualDisplayPanel() override;

public slots:
    void displayFormula(const QList<InputUnit> &formula) const;
    void displayAnswer(const qreal &result) const;
    void displayError(const ErrorCode &code) const;

private:
    QLabel *lblFormula;
    QLabel *lblAns;
    QVBoxLayout *VLay;

    void iniUI();
    //信号由父对象统一管理

};


#endif //GUICALCULATOR_DISPLAY_H