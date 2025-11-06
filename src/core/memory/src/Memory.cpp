#include "Memory.h"

#include <QMap>
#include <QDebug>

Memory::Memory(QObject *parent) {
    alpha = 0.0;
    beta = 0.0;
    gamma = 0.0;
    delta = 0.0;
    epsilon = 0.0;
    zeta = 0.0;
    xi = 0.0;
    lota = 0.0;
    mu = 0.0;
    ans = 0.0;
}

Memory::~Memory() = default;

qreal* Memory::mapVar(const QString &varName) {
    QMap<QString,qreal*> varMap{
            {"A",&alpha},{"B",&beta},{"C",&gamma},{"D",&delta},{"E",&epsilon},{"F",&zeta},
            {"X",&xi},{"Y",&lota},
            {"M",&mu},
            {"R",&ans}
    };
    return varMap[varName];
}

qreal Memory::getVar(const QString &varName) {
    return *mapVar(varName);
}

void Memory::setVar(const QString &varName,const qreal &value) {
    if (varName == "R") {
        qCritical() << "Cannot set variable ANS by Memory::setVar";
    }
    *mapVar(varName) = value;
    qDebug() << value << " -> " << varName;
}

void Memory::resetVar(const QString &varName) {
    if (varName == "R") {
        qCritical() << "Cannot reset variable ANS by Memory::resetVar";
    }
    *mapVar(varName) = 0.0;
    qDebug() << QString("Variable %1 cleared").arg(varName);
}

void Memory::memoryMuPlus(const qreal &value) {
    mu += value;
    qDebug() << "M += " << value;
}

void Memory::memoryMuMinus(const qreal &value) {
    mu -= value;
    qDebug() << "M -= " << value;
}

void Memory::receiveAns(const qreal &value) {
    ans = value;
}