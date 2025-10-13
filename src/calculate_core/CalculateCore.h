#ifndef GUICALCULATOR_CALCULATECORE_H
#define GUICALCULATOR_CALCULATECORE_H

#include "Memory.h"

#include <QObject>
#include <QString>
#include <QStringList>

class CalculateCore : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString formula READ formula WRITE setFormula NOTIFY formulaChanged)
    Q_PROPERTY(QString memory READ memory WRITE memoryStored NOTIFY memoryChanged)
public:
    explicit CalculateCore(QObject *parent = nullptr);
    ~CalculateCore();

    QString formula() const;

public slots:
    Q_INVOKABLE void setFormula(const QString &value);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void appendToFormula(const QChar &input);
    Q_INVOKABLE void chopFromFormula();

    Q_INVOKABLE void calculate();

private:
    QString m_formula = "#";
    qreal result = 0.0;

    int getPriority(const QChar &op1, const QChar &op2) const;
    void performOperation(const QString &num1, const QString &num2,const QChar &op) const;
    bool isOperator(const QChar &ch) const;
    bool isDigit(const QChar &ch) const;

signals:
    void formulaChanged();
    void calculateCompleted();
    void errorOccurred();
};


#endif //GUICALCULATOR_CALCULATECORE_H