#ifndef GUICALCULATOR_BASICINPUTPANEL_H
#define GUICALCULATOR_BASICINPUTPANEL_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>

class BasicInputPanel : private QWidget {
    Q_OBJECT

public:
    explicit BasicInputPanel(QWidget *parent = nullptr);
    ~BasicInputPanel() override;

public slots:

private:

signals:

};


#endif //GUICALCULATOR_BASICINPUTPANEL_H