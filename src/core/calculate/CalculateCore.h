#ifndef GUICALCULATOR_CALCULATECORE_H
#define GUICALCULATOR_CALCULATECORE_H

//#include "Memory.h"

#include "unit.h"
#include "errorCode.h"
#include <QObject>
#include <QString>

class CalculateCore : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<InputUnit> formula READ formula WRITE setFormula NOTIFY formulaChanged)

public:
    explicit CalculateCore(QObject *parent = nullptr);
    ~CalculateCore() override;

public slots:
    [[nodiscard]]QList<InputUnit> formula() const;
    [[nodiscard]]qreal result() const;
    void setFormula(const QList<InputUnit> &formula);
    void appendToFormula(const InputUnit &formula);
    void deleteFromFormula();
    void clearFormula();
    void do_calculate();

private:
    QList<InputUnit>* m_formula;
    QList<InputUnit>::iterator m_iterator;
    qreal m_result;
    bool finish = false;

    [[nodiscard]] static QChar getPriority(const QChar &op1, const QChar &op2);
    [[nodiscard]] static qreal performCalculation(const qreal &num1, const qreal &num2, const QChar &op);
    void calculate();

    void iniAutoClear();

signals:
    void formulaChanged(const QList<InputUnit> &formula);
    void calculateCompleted(const qreal &result);
    void errorOccurred(const ErrorCode &code,const InputUnit &onErrorInput, const QString &error);

    //void autoAppendAns(const InputUnit &formula);
    void autoClearFormula();

};

#endif //GUICALCULATOR_CALCULATECORE_H
