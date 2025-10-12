#ifndef GUICALCULATOR_MAINWINDOW_H
#define GUICALCULATOR_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Mainwindow;
}

QT_END_NAMESPACE

class Mainwindow : public QMainWindow {
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);

    ~Mainwindow() override;

private:
    Ui::Mainwindow *ui;
};


#endif //GUICALCULATOR_MAINWINDOW_H