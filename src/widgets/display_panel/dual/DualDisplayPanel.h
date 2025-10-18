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
    void setCurrentDisplay(const QString &display) const;
    void setPreviousDisplay(const QString &display) const;

private:
    QLabel *lblPreviousDisplay;
    QLabel *lblCurrentDisplay;
    QVBoxLayout *VLay;

    void iniUI();
    //信号由父对象统一管理

};


#endif //GUICALCULATOR_DISPLAY_H