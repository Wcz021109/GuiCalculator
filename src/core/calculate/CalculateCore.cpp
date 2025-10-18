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
    return QString::number(m_result, 'g', 15);
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

void CalculateCore::appendToFormula(const QString &input) {
    m_formula.append(input);
    emit formulaChanged();
}

void CalculateCore::chopFromFormula(const qint32 &chopNum) {
    if (m_formula.length() > chopNum) {
        m_formula.chop(chopNum);
        emit formulaChanged();
    }
}

QChar CalculateCore::getPriority(const QChar &op1, const QChar &op2) {
    static QMap<QChar, QMap<QChar, QChar> > opMap{
        {'+', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'-', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'*', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'/', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'^', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'F', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '='}, {'#', '!'}}},
        {'(', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '='}, {'#', '!'}}},
        {')', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'^', '>'}, {'F', '!'},{'(', '!'}, {')', '>'}, {'#', '>'}}},
        {'#', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'^', '<'}, {'F', '<'},{'(', '<'}, {')', '!'}, {'#', '='}}}
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

bool CalculateCore::isDigit(const QChar &ch) noexcept {
    return ch.isDigit() || ch == "." || ch == "!";
}

bool CalculateCore::isLower(const QChar &ch) noexcept {
    return ch.isLower();
}

bool CalculateCore::isUpper(const QChar &ch) noexcept {
    return ch.isUpper();
}

bool CalculateCore::isOperator(const QChar &ch) noexcept {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')' || ch == ',' || ch == '%' || ch == '#';
}

void CalculateCore::calculate() {
    QStack<qreal> OPND;
    QStack<QChar> OPTR;
    QStack<QString> OPWD;

    OPTR.push('#');

    const QChar *ptr = m_formula.constData();
    const QChar *start = m_formula.constBegin();
    const QChar *end = m_formula.constEnd();
    while (ptr < end) {
        if (isDigit(*ptr)||(ptr == start && *ptr=='-')) {
            QString number;
            bool ok;
            if (*ptr == '!'||*ptr == '-') {
                number.append('-');
                ptr++;
                if (ptr >= end) break;
            }
            while (ptr < end && (isDigit(*ptr) || *ptr == '.')) {
                number.append(*ptr);
                ptr++;
            }
            if (*ptr == '%') {
                OPND.push(number.toDouble(&ok) * 0.01);
                ptr++;
            }
            else OPND.push(number.toDouble(&ok));
            if (!ok) {
                errorCode = QString(R"("Math error: Invalid number: "%1".)").arg(number);
                emit errorOccurred();
                return;
            }
        } else if (isLower(*ptr)) {
            QString opFunction;
            while (ptr < end && !isOperator(*ptr)) {
                opFunction.append(ptr);
                ptr++;
            }
            if (*ptr != '(') {
                errorCode = "Syntax error: Invalid usage of functions.";
                emit errorOccurred();
                return;
            }
            OPWD.push(opFunction);
            OPTR.push('F');
            ptr++;
        } else if (isUpper(*ptr)) {
            QString opConst;
            while (ptr < end && isUpper(*ptr)) {
                opConst.append(ptr);
                ptr++;
            }
            if (!isOperator(*ptr) || *ptr == '(') {
                errorCode = "Syntax error: Invalid usage of const.";
                emit errorOccurred();
                return;
            }
            //OPND.push(Function::searchConst(opConst))
        } else if (isOperator(*ptr)) {
            if (*ptr != '(' && (ptr == start || isOperator(*(ptr - 1)))) break;
            QChar priority = getPriority(OPTR.top(), *ptr);
            switch (priority.unicode()) {
                case '>': {
                    if (OPTR.size() < 2) {
                        errorCode = "Stack error.";
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
                    OPTR.push(*ptr);
                    ptr++;
                    break;
                case '=':
                    if (OPTR.pop() == 'F') {
                        //qreal funcValue = Function::calculateFunc(OPWD.pop(),OPND.pop());
                        //OPND.push(funcValue);
                    }
                    ptr++;
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
        } else {
            if (isOperator(*ptr)) errorCode = "Syntax error: Unexpected operator.";
            else errorCode = QString(R"("Syntax error: Invalid operator: "%1".")").arg(*ptr);
            emit errorOccurred();
            break;
        }
    }
    m_result = OPND.top();
    emit calculateCompleted();
}
