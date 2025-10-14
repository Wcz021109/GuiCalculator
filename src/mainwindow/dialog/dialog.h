#ifndef GUICALCULATOR_ERRORDIALOG_H
#define GUICALCULATOR_ERRORDIALOG_H

#include <QDialog>

class errorDialog : public QDialog {
    Q_OBJECT

public:
    explicit errorDialog(QWidget *parent = nullptr);
    ~errorDialog() override;

private:
};


#endif //GUICALCULATOR_ERRORDIALOG_H