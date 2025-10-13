#include "CalculateCore.h"

#include <QStack>
#include <QMap>
#include <QDebug>

CalculateCore::CalculateCore(QObject *parent)
    : QObject(parent){
    //  初始化代码
}

CalculateCore::~CalculateCore() {

}

QString CalculateCore::formula() const{
    return m_formula;
}

void CalculateCore::setFormula(const QString &value) {
    if (m_formula != value) {
        m_formula = value;
        emit formulaChanged();
    }
}
void CalculateCore::clear() {
    m_formula = "#";
    result = 0.0;
    emit formulaChanged();
}
void CalculateCore::appendToFormula(const QChar &input){
    m_formula.append(input);
    emit formulaChanged();
}
void CalculateCore::chopFromFormula() {
    if (m_formula.length() > 1) {
        m_formula.chop(1);
        emit formulaChanged();
    }else {
        qCritical() << "formula is empty";
    }
}

int CalculateCore::getPriority(const QChar &op1, const QChar &op2) const {
    static QMap<QChar, QMap<QChar,QChar>> opMap{
        {'+',{{'+','>'},{'-','>'},{'*','<'},{'/','<'},{'^','<'},{'(','<'},{')','>'},{'#','>'}}},
        {'-',{{'+','>'},{'-','>'},{'*','<'},{'/','<'},{'^','<'},{'(','<'},{')','>'},{'#','>'}}},
        {'*',{{'+','>'},{'-','>'},{'*','>'},{'/','>'},{'^','<'},{'(','<'},{')','>'},{'#','>'}}},
        {'/',{{'+','>'},{'-','>'},{'*','>'},{'/','>'},{'^','<'},{'(','<'},{')','>'},{'#','>'}}},
        {'^',{{'+','>'},{'-','>'},{'*','>'},{'/','>'},{'^','>'},{'(','<'},{')','>'},{'#','>'}}},
        {'(',{{'+','>'},{'-','>'},{'*','>'},{'/','>'},{'^','>'},{'(','>'},{')','='},{'#','!'}}},
        {')',{{'+','>'},{'-','>'},{'*','>'},{'/','>'},{'^','>'},{'(','!'},{')','>'},{'#','>'}}},
        {'#',{{'+','<'},{'-','<'},{'*','<'},{'/','<'},{'^','<'},{'(','<'},{')','!'},{'#','='}}}
    };
    QChar relation=opMap[op1][op2];
    switch (relation.unicode()) {
        case '>' : return 2;break;
        case '=': return 0;break;
        case '<': return 1;break;
        case '!': return -1;break;
        default: return -2;break;
    }
}
void CalculateCore::performOperation(const QString &num1, const QString &num2,const QChar &op) const{}
bool CalculateCore::isOperator(const QChar &ch) const {
    if (ch=="+"||ch=="-"||ch=="*"||ch=="/"||ch=="^"||ch=="("||ch==")"||ch=="#") return true;
    else return false;
}
bool CalculateCore::isDigit(const QChar &ch) const {
    return false;
}

void CalculateCore::calculate() {
    QStack<QChar> OPND;
    QStack<qreal> OPTR;
}
