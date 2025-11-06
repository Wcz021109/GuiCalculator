#include "CalculateCore.h"

#include "Function.h"
#include <QStack>
#include <QMap>
#include <QDebug>

CalculateCore::CalculateCore(QObject *parent):
        QObject(parent),
        memory(nullptr),
        m_formula()
{
    memory = new Memory(this);
    try {
        m_formula = new QList<InputUnit>();
        m_iterator = m_formula->end();
        m_result = 0;
    }catch (std::exception &e) {
        qCritical() << "CalculateCore::Initialization failed: " << e.what();
        exit(-1);
    }
    connect(this,&CalculateCore::calculateCompleted,memory,&Memory::receiveAns);
}

CalculateCore::~CalculateCore() = default;

QList<InputUnit> CalculateCore::formula() const {
    return *m_formula;
}

qreal CalculateCore::result() const {
    return m_result;
}

void CalculateCore::setFormula(const QList<InputUnit> &formula) {
    *m_formula = formula;
    emit formulaChanged(*m_formula);
}

void CalculateCore::appendToFormula(const InputUnit &formula) {
    try {
        if (finish) {
            m_formula->clear();
            if (formula.keyType==InputType::Sign) m_formula->append(InputUnit("Ans","R",InputType::Memory));
            emit formulaChanged(*m_formula);
            finish = false;
        }
        if (!m_formula) throw std::runtime_error("Formula list is not initialized");
        m_formula->append(formula);
        emit formulaChanged(*m_formula);
    }    catch (const std::exception &e) {
        qCritical() << "CalculateCore::Exception in formulalist: " << e.what();
    }
}

void CalculateCore::performOpr(const OprUnit &opr) {
    switch (opr.opr) {
        case OprType::Delete: {
            if (!m_formula->isEmpty()) {
                if (finish) {
                    finish = false;
                    break;
                }
                m_formula->removeLast();
                emit formulaChanged(*m_formula);
            }
            break;
        }
        case OprType::Clear: {
            if (!m_formula->isEmpty()) {
                if (finish) finish = false;
                m_formula->clear();
                emit formulaChanged(*m_formula);
            }
            break;
        }
        case OprType::Calculate: {
            if (!m_formula->isEmpty()) {
                calculate();
            }
            break;
        }
        default:qCritical() << "Unknown operation"; break;
    }
}

void CalculateCore::performMemOpr(const MemOprUnit &mem){
    InputUnit m_unit = InputUnit("",InputType::Operation);
    switch (mem.memOpr) {
        case MemOpr::Clear: {
            memory->resetVar(mem.varName);
            break;
        }
        case MemOpr::Read: {
            InputUnit input_unit = InputUnit(mem.varName,InputType::Memory);
            if (finish == true || m_formula->isEmpty()) {
                m_result = memory->getVar(mem.varName);
                emit calculateCompleted(m_result);
            }
            appendToFormula(input_unit);
            break;
        }
        case MemOpr::Store: {
            if (finish) appendToFormula(InputUnit("Ans","R",InputType::Memory));
            if (!m_formula->isEmpty()) {
                m_unit.keyName.append("->");
                m_unit.keyName.append(mem.varName);
                calculate();
                memory->setVar(mem.varName, m_result);
                m_formula->append(m_unit);
                emit formulaChanged(*m_formula);
            }
            break;
        }
        case MemOpr::Add: {
            if (finish) appendToFormula(InputUnit("Ans","R",InputType::Memory));
            if (!m_formula->isEmpty()) {
                m_unit.keyName.append("M+");
                calculate();
                memory->memoryMuPlus(m_result);
                m_formula->append(m_unit);
                emit formulaChanged(*m_formula);
            }
            break;
        }
        case MemOpr::Substract: {
            if (finish) appendToFormula(InputUnit("Ans","R",InputType::Memory));
            if (!m_formula->isEmpty()) {
                if (finish) appendToFormula(InputUnit("Ans","R",InputType::Memory));
                m_unit.keyName.append("M-");
                calculate();
                memory->memoryMuMinus(m_result);
                m_formula->append(m_unit);
                emit formulaChanged(*m_formula);
            }
            break;
        }
        default:qCritical() << "Unknown operation!"; break;
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

qreal CalculateCore::performCalculation(const qreal &num2, const qreal &num1, const QChar &tr) {
    switch (tr.unicode()) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': {
            if (num2 == 0.0) {
                throw std::domain_error("Division by zero");
            }
            return num1 / num2;
        }
        case 'S': return num1 * pow(10,num2);
        case '^': return pow(num1, num2);
        default: throw std::invalid_argument("Invalid operation");
    }
}

void CalculateCore::calculate() try{
    m_formula->append(InputUnit( "#", InputType::Sign));
    QStack<qreal> OPND;
    QStack<QChar> OPTR;
    QStack<QString> OPFC;

    OPTR.push('#');

    m_iterator = m_formula->begin();
    if (m_iterator == m_formula->end()) {
        qDebug() << "Empty formula";
        return;
    }
    if (m_iterator->keyValue == "+"|| m_iterator->keyValue == "-") {
        m_iterator->keyType = InputType::Digit;
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
                    throw std::invalid_argument("Invalid number");
                }
                if (m_iterator->keyType == InputType::Suffix) {
                    m_num = Function::performSuffix(m_num, m_iterator->keyValue);
                    ++m_iterator;
                }
                OPND.push(m_num);
                break;
            }
            case InputType::Function: {
                OPFC.push(m_iterator->keyValue);
                OPTR.push('F');
                ++m_iterator;
                break;
            }
            case InputType::Const: {
                OPND.push(Function::getConst(m_iterator->keyValue));
                ++m_iterator;
                if (m_iterator->keyType != InputType::Sign || m_iterator->keyValue == '(') {
                    --m_iterator;
                    throw std::invalid_argument("Invalid usage of constants");
                }
                break;
            }
            case InputType::Memory: {
                OPND.push(memory->getVar(m_iterator->keyValue));
                ++m_iterator;
                if (m_iterator->keyType != InputType::Sign || m_iterator->keyValue == '(') {
                    --m_iterator;
                    throw std::invalid_argument("Invalid usage of variables");
                }
            }
            case InputType::Sign: {
                QChar priority = getPriority(OPTR.top(), m_iterator->keyValue.at(0));
                switch (priority.unicode()) {
                    case '>': {
                        if (OPND.size() < 2) throw std::invalid_argument("Continuous operators");
                        OPND.push(performCalculation(OPND.pop(), OPND.pop(), OPTR.pop()));
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
                            qreal funcValue = Function::performFormula(OPFC.pop(), OPND.pop());
                            OPND.push(funcValue);
                        }
                        ++m_iterator;
                        break;
                    }
                    case '!': throw std::invalid_argument("Invalid usage of operator");
                    default: throw std::invalid_argument("Unrecognized operator");
                }
                break;
            }
            default: throw std::invalid_argument("Unrecognized input");
        }
    }
    if (OPND.isEmpty()) throw std::invalid_argument("Empty formula");
    m_result = OPND.top();
    qDebug() << "Result: " << m_result;
    m_formula->removeLast();
    qDebug() << "CalculateCore::Calculate completed";
    emit calculateCompleted(m_result);
    finish = true;
} catch (const std::bad_alloc &e) {
    m_formula->removeLast();
    qCritical() << "CalculateCore::Calculate failed: " << e.what();
    emit errorOccurred(ErrorCode::Stack_error, InputUnit(), e.what());
} catch (std::overflow_error &e) {
    m_formula->removeLast();
    qCritical() << "CalculateCore::Calculate failed: " << e.what();
    emit errorOccurred(ErrorCode::Stack_error, InputUnit(), e.what());
} catch (std::out_of_range &e) {
    m_formula->removeLast();
    qCritical() << "CalculateCore::Calculate failed: " << e.what();
    emit errorOccurred(ErrorCode::Stack_error, InputUnit(), e.what());
} catch (std::invalid_argument &e) {
    m_formula->removeLast();
    qCritical() << "CalculateCore::Calculate failed: " << e.what();
    emit errorOccurred(ErrorCode::Invalid_argument, *m_iterator, e.what());
} catch (std::domain_error &e) {
    m_formula->removeLast();
    qCritical() << "CalculateCore::Calculate failed: " << e.what();
    emit errorOccurred(ErrorCode::Domain_error, *m_iterator, e.what());
} catch (std::logic_error &e) {
    m_formula->removeLast();
    qCritical() << "CalculateCore::Calculate failed: " << e.what();
    emit errorOccurred(ErrorCode::Logic_error, *m_iterator, e.what());
} catch (std::exception &e) {
    m_formula->removeLast();
    qCritical() << "CalculateCore::Calculate failed: " << e.what();
    emit errorOccurred(ErrorCode::Other, InputUnit(), e.what());
}
