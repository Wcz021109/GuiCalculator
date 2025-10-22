#ifndef GUICALCULATOR_CALCULATECORE_H
#define GUICALCULATOR_CALCULATECORE_H

//#include "Memory.h"

#include "unit.h"
#include "errorCode.h"
#include <QObject>
#include <QString>

class CalculateCore : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString formula READ formula WRITE setFormula NOTIFY formulaChanged)

public:
    explicit CalculateCore(QObject *parent = nullptr);
    ~CalculateCore() override;

public slots:
    void do_calculate(const QList<InputUnit> &formula);

private:
    [[nodiscard]] static QChar getPriority(const QChar &op1, const QChar &op2);
    [[nodiscard]] bool performCalculation(const qreal &num1, const qreal &num2, const QChar &op, qreal &result);

signals:
    void calculateCompleted(QString result);
    void errorOccurred(ErrorCode errorCode, QString error);

};

#endif //GUICALCULATOR_CALCULATECORE_H
