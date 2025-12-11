#ifndef GUICALCULATOR_CALCULATECORE_H
#define GUICALCULATOR_CALCULATECORE_H

#include "Memory.h"

#include "unit.h"
#include "error.h"
#include <QObject>
#include <QString>

class CalculateCore : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<InputUnit> formula READ formula WRITE setFormula NOTIFY formulaChanged)
    Q_PROPERTY(qreal result READ result NOTIFY calculateCompleted)

public:
    explicit CalculateCore(QObject *parent = nullptr);
    ~CalculateCore() override;

public slots:
    [[nodiscard]]QList<InputUnit> formula() const;
    [[nodiscard]]qreal result() const;
    void setFormula(const QList<InputUnit> &formula);
    void appendToFormula(const InputUnit &formula);
    void performOpr(const OprUnit &opr);
    void performMemOpr(const MemOprUnit &mem);

private:
    Memory* memory;

    QList<InputUnit>* m_formula;
    qreal m_result;
    bool finish = false;

    [[nodiscard]] static QChar getPriority(const QChar &op1, const QChar &op2);
    [[nodiscard]] static qreal performCalculation(const qreal &num1, const qreal &num2, const QChar &op);
    void calculate();

signals:
    void formulaChanged(const QList<InputUnit> &formula);
    void calculateCompleted(qreal result);
    void errorOccurred(const ErrorCode &code,const QString &error);
};

#endif //GUICALCULATOR_CALCULATECORE_H
