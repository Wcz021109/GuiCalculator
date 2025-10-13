#ifndef GUICALCULATOR_CALCULATECORE_H
#define GUICALCULATOR_CALCULATECORE_H

//  #include "Memory.h"

#include <QObject>
#include <QString>
#include <QStringList>

class CalculateCore : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString formula READ formula WRITE setFormula NOTIFY formulaChanged)

public:
    explicit CalculateCore(QObject *parent = nullptr);

    ~CalculateCore();

    QString formula() const;
    QString error() const;
    QString result() const;

    Q_INVOKABLE void setFormula(const QString &value);

    Q_INVOKABLE void clear();

    Q_INVOKABLE void appendToFormula(const QChar &input);

    Q_INVOKABLE void chopFromFormula();

    Q_INVOKABLE void calculate();

private:
    QString m_formula;
    qreal m_result = 0.0;
    QString errorCode;

    QChar getPriority(const QChar &op1, const QChar &op2) const;

    bool performCalculation(const qreal &num1, const qreal &num2, const QChar &op, qreal &result);

    bool isOperator(const QChar &ch) const;

    bool isDigit(const QChar &ch) const;

signals:
    void formulaChanged();

    void calculateCompleted();

    void errorOccurred();
};


#endif //GUICALCULATOR_CALCULATECORE_H
