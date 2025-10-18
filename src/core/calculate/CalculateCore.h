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

public slots:
    void setFormula(const QString &value);
    void appendToFormula(const QString &input);
    void chopFromFormula(const qint32 &chopNum);
    void clear();
    void calculate();

private:
    QString m_formula;
    qreal m_result = 0.0;
    QString errorCode;

    [[nodiscard]] static bool isDigit(const QChar &ch) noexcept;
    [[nodiscard]] static bool isLower(const QChar &ch) noexcept;
    [[nodiscard]] static bool isUpper(const QChar &ch) noexcept;
    [[nodiscard]] static bool isOperator(const QChar &ch) noexcept;

    [[nodiscard]] static QChar getPriority(const QChar &op1, const QChar &op2);
    [[nodiscard]] bool performCalculation(const qreal &num1, const qreal &num2, const QChar &op, qreal &result);

signals:
    void formulaChanged();
    void calculateCompleted();
    void errorOccurred();

};

#endif //GUICALCULATOR_CALCULATECORE_H
