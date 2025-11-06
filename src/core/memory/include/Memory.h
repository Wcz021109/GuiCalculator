#ifndef GUICALCULATOR_MEMORY_H
#define GUICALCULATOR_MEMORY_H

#include <QObject>

class Memory : public QObject {
    Q_OBJECT

public:
    explicit Memory(QObject *parent = nullptr);
    ~Memory() override;

    [[nodiscard]]qreal getVar(const QString &varName);
    void setVar(const QString &varName,const qreal &value);
    void resetVar(const QString &varName);
    void memoryMuPlus(const qreal &value);
    void memoryMuMinus(const qreal &value);

public slots:
    void receiveAns(const qreal &value);

private:
    qreal alpha;
    qreal beta;
    qreal gamma ;
    qreal delta ;
    qreal epsilon;
    qreal zeta;
    qreal xi;
    qreal lota;
    qreal mu;
    qreal ans;

    qreal* mapVar(const QString &varName);
};


#endif //GUICALCULATOR_MEMORY_H