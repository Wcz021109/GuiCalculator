#include "CalculateCore.h"

#include <QStack>
#include <QDebug>

CalculateCore::CalculateCore(QObject *parent)
    : QObject(parent) {
    //  初始化代码
}

CalculateCore::~CalculateCore() = default;

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

QChar CalculateCore::getPriority(const QChar &op1, const QChar &op2) {
    static QMap<QChar, QMap<QChar, QChar> > opMap{
        {'+', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'-', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'*', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'/', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '<'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'^', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '>'}, {'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'(', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'(', '<'}, {')', '='}, {'#', '!'}}},
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
                errorCode = "Math error: Division by zero.";
                break;
            }
            result = num1 / num2;
            break;
        }
        case '^': result = pow(num1, num2);
            break;
        default: errorCode = "Syntax error: Invalid operation.";
            return false;
    }
    return true;
}

bool CalculateCore::checkSign(const qint32 &num ) const noexcept {
    QChar ch = m_formula.at(num);
    return ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "^" || ch == "(" || ch == ")" || ch == "#";
}
bool CalculateCore::isUnarySign(const qint32 &num) const noexcept {
    if (checkSign(num)){
        const QChar ch = m_formula.at(num);
        if (num==0) {
            return (ch=='+'||ch=='-');
        }else if (checkSign(num-1)){
            return  (ch == '+' || ch == '-' )&&m_formula.at(num-1)!=')';
        }
    }return false;
}

bool CalculateCore::isDigit(const qint32 &num) const noexcept {
    return m_formula.at(num).isDigit() || m_formula.at(num) == ".";
}

bool CalculateCore::isOperator(const qint32 &num) const noexcept {
    if (checkSign(num)&&!isUnarySign(num)) {
        const QChar ch = m_formula.at(num);
        if (num==0) return ch=='(';
        else if (ch=='(') return checkSign(num-1);
        else return m_formula.at(num-1).isDigit()||m_formula.at(num-1)==')';
    }
    return false;
}

void CalculateCore::calculate() {
    QStack<qreal> OPND;
    QStack<QChar> OPTR;

    OPTR.push('#');
    for (qint32 i = 0; i < m_formula.length();) {
        QChar ch = (i < m_formula.length()) ? m_formula.at(i) : '#';

        if (isDigit(i)||isUnarySign(i)) {
            QString number;
            bool ok;
            if (isUnarySign(i)) {
                number.append(ch);
                i++;
            }
            while (i < m_formula.length() && (isDigit(i) || m_formula.at(i) == '.')) {
                number.append(m_formula.at(i));
                i++;
            }
            OPND.push(number.toDouble(&ok));
            if (!ok) {
                errorCode = QString(R"("Math error: Invalid number: "%1".)").arg(number);
                emit errorOccurred();
                return;
            }
        } else if (isOperator(i)) {
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
                    errorCode = "Syntax error: Unexpected bracket.";
                    emit errorOccurred();
                    break;
                default:
                    errorCode = "Syntax error: Invalid operation.";
                    emit errorOccurred();
                    break;
            }
        }else {
            if (checkSign(i)) errorCode = "Syntax error: Unexpected operator.";
            else errorCode = QString(R"("Syntax error: Invalid operator: "%1".")").arg(m_formula.at(i));
            emit errorOccurred();
            break;
        }
    }
    m_result = OPND.top();
    emit calculateCompleted();
}
