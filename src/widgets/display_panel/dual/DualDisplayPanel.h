#ifndef GUICALCULATOR_DISPLAY_H
#define GUICALCULATOR_DISPLAY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DualDisplayPanel : public QWidget{
    Q_OBJECT;

public:
    explicit DualDisplayPanel(QWidget *parent);
    ~DualDisplayPanel() override;

public slots:
    [[nodiscard]] QString CurrentFormula() const;
    [[nodiscard]] QString PreviousFormula() const;
    void setDisplay(const QString &formula);
    void appendToDisplay(const QString &str);
    void chopFromDisplay();
    void displayResult(const QString &result);
    void displayError(const QString &errorCode);
    [[nodiscard]] QString formulaRecording() const;
    void clearCurrentDisplay();
    void clearAllDisplay();

private:
    QLabel *lblPreviousDisplay;
    QLabel *lblCurrentDisplay;
    QVBoxLayout *VLay;

    QString r_formula;

    void iniUI();
    //信号由父对象统一管理

signals:
    void displayChanged();
    void recordFormula();
};


#endif //GUICALCULATOR_DISPLAY_H