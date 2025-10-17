#ifndef GUICALCULATOR_MEMORYPANEL_H
#define GUICALCULATOR_MEMORYPANEL_H

#include <QWidget>
#include <QPushButton>

class MemoryPanel : public QWidget{
    Q_OBJECT

public:
    explicit MemoryPanel(QWidget *parent = nullptr);

    ~MemoryPanel() override;

public slots:

private:

signals:

};


#endif //GUICALCULATOR_MEMORYPANEL_H