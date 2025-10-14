#ifndef GUICALCULATOR_CALCULATECORE_H
#define GUICALCULATOR_CALCULATECORE_H

//#include "Memory.h"

#include <QObject>
#include <QString>
#include <QStringList>

class CalculateCore : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString formula READ formula WRITE setFormula NOTIFY formulaChanged)

public:
    explicit CalculateCore(QObject *parent = nullptr);

    ~CalculateCore() override;

    [[nodiscard]] QString formula() const;

    [[nodiscard]] QString error() const;

    [[nodiscard]] QString result() const;

    Q_INVOKABLE void setFormula(const QString &value);

    Q_INVOKABLE void clear();

    Q_INVOKABLE void appendToFormula(const QChar &input);

    Q_INVOKABLE void chopFromFormula();

    Q_INVOKABLE void calculate();

private:
    QString m_formula;
    qreal m_result = 0.0;
    QString errorCode;

    [[nodiscard]] static QChar getPriority(const QChar &op1, const QChar &op2);

    [[nodiscard]] bool performCalculation(const qreal &num1, const qreal &num2, const QChar &op, qreal &result);

    [[nodiscard]] bool checkSign(const qint32 &num) const noexcept;

    [[nodiscard]] bool isUnarySign(const qint32 &num) const noexcept;

    [[nodiscard]] bool isDigit(const qint32 &num) const noexcept;

    [[nodiscard]] bool isOperator(const qint32 &num) const noexcept;

signals:
    void formulaChanged();

    void calculateCompleted();

    void errorOccurred();
};


#endif //GUICALCULATOR_CALCULATECORE_H
