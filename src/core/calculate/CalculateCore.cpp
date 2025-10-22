#include "CalculateCore.h"
#include <QStack>
#include <QMap>

CalculateCore::CalculateCore(QObject *parent)
    : QObject(parent) {
    //  初始化代码
}

CalculateCore::~CalculateCore() = default;

QChar CalculateCore::getPriority(const QChar &op1, const QChar &op2) {
    static QMap<QChar, QMap<QChar, QChar> > opMap{
        {'+', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'S','<'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'-', {{'+', '>'}, {'-', '>'}, {'*', '<'}, {'/', '<'}, {'S','<'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'*', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'S','<'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'/', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'S','<'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'S', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'S','!'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'^', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'S','>'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '>'}, {'#', '>'}}},
        {'F', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'S','<'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '='}, {'#', '!'}}},
        {'(', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'S','<'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '='}, {'#', '!'}}},
        {')', {{'+', '>'}, {'-', '>'}, {'*', '>'}, {'/', '>'}, {'S','>'},{'^', '>'}, {'F', '!'},{'(', '!'}, {')', '>'}, {'#', '>'}}},
        {'#', {{'+', '<'}, {'-', '<'}, {'*', '<'}, {'/', '<'}, {'S','<'},{'^', '<'}, {'F', '<'},{'(', '<'}, {')', '!'}, {'#', '='}}}
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
                errorOccurred(ErrorCode::Math_error, "Division by zero");
                break;
            }
            result = num1 / num2;
            break;
        }
        case 'S': result = num1 * pow(10,num2);
            break;
        case '^': result = pow(num1, num2);
            break;
        default: errorOccurred(ErrorCode::Syntax_error, "Invalid operation");
            return false;
    }
    return true;
}

void CalculateCore::do_calculate(const QList<InputUnit> &formula) {
    QStack<qreal> OPND;
    QStack<QChar> OPTR;
    QStack<QString> OPFC;

    OPTR.push('#');

    QList<InputUnit>::const_iterator formula_iterator = formula.constBegin();
    while (formula_iterator < formula.constEnd()) {
        if (formula_iterator->keyType == InputType::Digit
            || (formula_iterator==formula.constBegin() && formula_iterator->keyValue == "-")) {
            QString number;
            bool ok;
            if (formula_iterator->keyValue == "(-)"||formula_iterator->keyValue == "-") {
                number.append('-');
                ++formula_iterator;
                if (formula_iterator==formula.constEnd()) break;
            }
            while (formula_iterator < formula.constEnd() && formula_iterator->keyType == InputType::Digit) {
                number.append(formula_iterator->keyValue);
                ++formula_iterator;
            }
            qreal m_num = number.toDouble(&ok);
            if (!ok) {
                emit errorOccurred(ErrorCode::Math_error,QString(R"(Invalid number: "%1")").arg(number));
                return;
            }
            if (formula_iterator->keyType == InputType::Suffix) {
                //OPND.push(Memory::operateSuffix(m_num))
                OPND.push(m_num);
                ++formula_iterator;
            }else OPND.push(m_num);
        } else if (formula_iterator->keyType==InputType::Function) {
            OPFC.push(formula_iterator->keyValue);
            if (formula_iterator->keyValue != "(") {
                emit errorOccurred(ErrorCode::Syntax_error, "Invalid usage of functions");
                return;
            }
            OPTR.push('F');
            ++formula_iterator;
        } else if (formula_iterator->keyType == InputType::Const) {
            //OPND.push(Function::searchConst(opConst))
            ++formula_iterator;
            if (formula_iterator->keyType != InputType::Sign || formula_iterator->keyValue == '(') {
                emit errorOccurred(ErrorCode::Syntax_error,"Invalid usage of const");
                return;
            }
        } else if (formula_iterator->keyType == InputType::Sign) {
            QChar priority = getPriority(OPTR.top(), formula_iterator->keyValue.at(0));
            switch (priority.unicode()) {
                case '>': {
                    if (OPND.size() < 2) {
                        emit errorOccurred(ErrorCode::Syntax_error,"Invalid operators");
                        return;
                    }
                    qreal b = OPND.pop();
                    qreal a = OPND.pop();
                    QChar lastTr = OPTR.pop();
                    qreal r = 0;
                    if (!performCalculation(a, b, lastTr, r)) {
                        return;
                    }
                    OPND.push(r);
                    break;
                }
                case '<':
                    OPTR.push(formula_iterator->keyValue.at(0));
                    ++formula_iterator;
                    break;
                case '=':
                    if (OPTR.pop() == 'F') {
                        //qreal funcValue = Function::calculateFunc(OPFC.pop(),OPND.pop());
                        //OPND.push(funcValue);
                    }
                    ++formula_iterator;
                    break;
                case '!':
                    emit errorOccurred(ErrorCode::Syntax_error,"Unexpected bracket.");
                    return;
                default:
                    emit errorOccurred(ErrorCode::Syntax_error,"Invalid operation.");
                    return;;
            }
        } else {
            emit errorOccurred(ErrorCode::Dev_error,QString(R"(Unsupported key: "%1")").arg(formula_iterator->keyValue));
            return;
        }
    }
    emit calculateCompleted(QString::number(OPND.top()));
}