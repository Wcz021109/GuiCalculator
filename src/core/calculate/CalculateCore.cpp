#include "CalculateCore.h"
#include <QStack>
#include <QMap>
#include <QDebug>
#include <bits/regex_error.h>

CalculateCore::CalculateCore(QObject *parent):
    QObject(parent) {
    m_formula = new QList<InputUnit>();
    m_iterator = m_formula->end();
    m_result = 0;
}

CalculateCore::~CalculateCore() {
    delete m_formula;
}

QList<InputUnit> CalculateCore::formula() const {
    return *m_formula;
}

void CalculateCore::setFormula(const QList<InputUnit> &formula) {
    *m_formula = formula;
    emit formulaChanged(*m_formula);
}

void CalculateCore::appendToFormula(const InputUnit &formula) {
    m_formula->append(formula);
    emit formulaChanged(*m_formula);
}

void CalculateCore::deleteFromFormula() {
    m_formula->removeLast();
    emit formulaChanged(*m_formula);
}

void CalculateCore::clearFormula() {
    m_formula->clear();
    emit formulaChanged(*m_formula);
}

void CalculateCore::do_calculate(const MemOprUnit &memoryOperation) {
    if (!m_formula->isEmpty()) {
        try {
            calculate();
            emit calculateCompleted(m_result);
        }catch (std::domain_error &e) {
            emit errorOccurred(ErrorCode::Math_error, *m_iterator,e.what());
        }catch (std::logic_error &e) {
            emit errorOccurred(ErrorCode::Syntax_error, *m_iterator,e.what());
        }catch (std::out_of_range &e) {
            emit errorOccurred(ErrorCode::Stack_error, *nullptr, e.what());
        }catch (std::overflow_error &e) {}
        catch (std::invalid_argument &e) {
            emit errorOccurred(ErrorCode::Other,*m_iterator,e.what());
        }
    }
}


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

qreal CalculateCore::performCalculation(const qreal &num1, const qreal &num2, const QChar &tr) {
    switch (tr.unicode()) {
        case '+': return num1 + num2;
        case '-': return  num1 - num2;
        case '*': return num1 * num2;
        case '/': {
            if (num2 == 0.0) {
                throw std::domain_error("Division by zero");
            }
            return num1 / num2;
        }
        case 'S': return num1 * pow(10,num2);
        case '^': return pow(num1, num2);
        default: throw std::logic_error("Invalid operation");
    }
}

void CalculateCore::calculate() {
    QStack<qreal> OPND;
    QStack<QChar> OPTR;
    QStack<QString> OPFC;

    OPTR.push('#');

    m_iterator = m_formula->begin();
    if (m_iterator == m_formula->end()) {
        qDebug() << "Empty formula";
        m_result = 0;
    }
    while (m_iterator < m_formula->end()) {
        switch (m_iterator->keyType) {
            case InputType::Digit: {
                QString number;
                bool ok;
                while (m_iterator < m_formula->constEnd() && m_iterator->keyType == InputType::Digit) {
                    number.append(m_iterator->keyValue);
                    ++m_iterator;
                }
                qreal m_num = number.toDouble(&ok);
                if (!ok) {
                    throw std::logic_error("Invalid number");
                }
                if (m_iterator->keyType == InputType::Suffix) {
                    //OPND.push(Memory::operateSuffix(m_num))
                    OPND.push(m_num);
                    ++m_iterator;
                } else OPND.push(m_num);
                break;
            }
            case InputType::Function: {
                OPFC.push(m_iterator->keyValue);
                if (m_iterator->keyValue != "(") {
                    --m_iterator;
                    ++m_iterator;
                    throw std::logic_error("Invalid usage of functions");
                }
                OPTR.push('F');
                break;
            }
            case InputType::Const: {
                //OPND.push(Function::searchConst(opConst))
                ++m_iterator;
                if (m_iterator->keyType != InputType::Sign || m_iterator->keyValue == '(') {
                    --m_iterator;
                    throw std::logic_error("Invalid usage of constants");
                }
                break;
            }
            case InputType::Sign: {
                QChar priority = getPriority(OPTR.top(), m_iterator->keyValue.at(0));
                switch (priority.unicode()) {
                    case '>': {
                        if (OPND.size() < 2) throw std::logic_error("Continuous operators");
                        qreal b = OPND.pop();
                        qreal a = OPND.pop();
                        QChar t = OPTR.pop();
                        qreal r = 0;
                        r =performCalculation(a, b, t);
                        OPND.push(r);
                        break;
                    }
                    case '<': {
                        OPTR.push(m_iterator->keyValue.at(0));
                        ++m_iterator;
                        if (m_iterator->keyValue == "+"|| m_iterator->keyValue == "-") {
                            m_iterator->keyType = InputType::Digit;
                        }
                        break;
                    }
                    case '=': {
                        if (OPTR.pop() == 'F') {
                            //qreal funcValue = Function::calculateFunc(OPFC.pop(),OPND.pop());
                            //OPND.push(funcValue);
                        }
                        ++m_iterator;
                        break;
                    }
                    case '!': throw std::domain_error("Invalid usage of operator");
                    default: throw std::invalid_argument("Unrecognized operator");
                }
            break;
            }
            default: throw std::invalid_argument("Unknown error");
        }
    }
    m_result = OPND.top();
    qDebug() << "Result: " << m_result;
}
