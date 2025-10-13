#include "CalculateCore.h"

#include <QStack>
#include <QMap>
#include <QDebug>

CalculateCore::CalculateCore(QObject *parent)
    : QObject(parent) {
    //  初始化代码
}

CalculateCore::~CalculateCore() {
}

QString CalculateCore::formula() const {
    return m_formula;
}

QString CalculateCore::error() const {
    return errorCode;
}

QString CalculateCore::result() const {
    return QString::number(m_result,'g',15);
}

void CalculateCore::setFormula(const QString &value) {
    if (m_formula != value) {
        m_formula = value;
        emit formulaChanged();
    }
}

void CalculateCore::clear() {
    m_formula.clear();
    m_result = 0.0;
    emit formulaChanged();
}

void CalculateCore::appendToFormula(const QChar &input) {
    m_formula.append(input);
    emit formulaChanged();
}

void CalculateCore::chopFromFormula() {
    if (m_formula.length() > 1) {
        m_formula.chop(1);
        emit formulaChanged();
    }
}

QChar CalculateCore::getPriority(const QChar &op1, const QChar &op2) const {
    static QMap<QChar, QMap<QChar, QChar> > opMap{
        {'+', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'-', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'*', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'/', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'^', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '>'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'(', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '>'}, {'(', '>'}, {')', '='}, {'#', '!'}}},
        {')', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '>'}, {'(', '!'}, {')', '>'}, {'#', '>'}}},
        {'#', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'(', '<'}, {')', '!'}, {'#', '='}}}
    };
    return opMap[op1][op2];
}

bool CalculateCore::performCalculation(const qreal &num1, const qreal &num2, const QChar &tr, qreal &result) {
    switch (tr.unicode()) {
        case '+': result = num1 + num2;
            break;
        case '-': result = num1 - num2;
            break;
        case '*': result = num1 * num2;
            break;
        case '/': {
            if (num2 == 0.0) {
                errorCode = "Math error";
                return false;
            }
            result = num1 / num2;
            break;
        }
        case '^': result = pow(num1, num2);
            break;
        default: errorCode = "Invalid operation";
            return false;
    }
    return true;
}

bool CalculateCore::isOperator(const QChar &ch) const {
    if (ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "^" || ch == "(" || ch == ")" || ch == "#")
        return true;
    else return false;
}

bool CalculateCore::isDigit(const QChar &ch) const {
    return ch.isDigit() || ch == ".";
}

void CalculateCore::calculate() {
    QStack<qreal> OPND;
    QStack<QChar> OPTR;

    OPTR.push('#');

    QString expression = m_formula;
    for (int i = 0; i < expression.length() || OPTR.top() != '#';) {
        QChar ch = (i < expression.length()) ? expression.at(i) : '#';

        if (isDigit(expression.at(i))) {
            QString number;
            bool ok;
            while (i < expression.length() && (isDigit(expression.at(i)) || expression.at(i) == '.')) {
                number.append(expression.at(i));
                i++;
            }
            OPND.push(number.toDouble(&ok));
            if (!ok) {
                errorCode = "Parse error";
                emit errorOccurred();
                return;
            }
        } else if (isOperator(ch)) {
            QChar priority = getPriority(OPTR.top(), ch);
            switch (priority.unicode()) {
                case '>': {
                    if (OPTR.size() < 2) {
                        errorCode = "Stack error";
                        emit errorOccurred();
                        return;
                    }
                    qreal b = OPND.pop();
                    qreal a = OPND.pop();
                    QChar lastTr = OPTR.pop();
                    qreal r = 0;
                    if (!performCalculation(a, b, lastTr, r)) {
                        errorOccurred();
                        return;
                    }
                    OPND.push(r);
                    OPTR.push(ch);
                    break;
                }
                case '<':
                    OPTR.push(ch);
                    i++;
                    break;
                case '=':
                    OPTR.pop();
                    i++;
                    break;
                case '!':
                    errorCode = "Math error";
                    emit errorOccurred();
                    return;
                default:
                    errorCode = "Invalid operation";
                    emit errorOccurred();
                    return;
            }
        }
    }
    m_result = OPND.top();
    emit calculateCompleted();
}
