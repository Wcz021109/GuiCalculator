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
    void appendToDisplay(const QChar &ch);
    void chopFromDisplay();
    void displayResult(const QString &result);
    void displayError(const QString &errorCode);
    void clearCurrentDisplay();
    void clearAllDisplay();

private:
    QLabel *lblPreviousDisplay;
    QLabel *lblCurrentDisplay;
    QVBoxLayout *VLay;

    void iniUI();
    static void iniSignalSlots();

signals:
    void displayChanged();
};


#endif //GUICALCULATOR_DISPLAY_H