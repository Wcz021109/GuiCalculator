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
    m_formula = new QList<InputUnit>();
    m_result = 0;
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

void CalculateCore::appendToFormula(const InputUnit &formula) try {
    if (!m_formula) throw std::runtime_error("Formula list is not initialized");
    if (finish) {
        m_formula->clear();
        if (formula.keyType == InputType::Sign) m_formula->append(InputUnit("Ans", "R", InputType::Memory));
        finish = false;
    }
    m_formula->append(formula);
    emit formulaChanged(*m_formula);
} catch (const std::exception &e) {
    qCritical() << "CalculateCore::Exception in formulalist: " << e.what();
}

void CalculateCore::performOpr(const OprUnit &opr) {
    switch (opr.opr) {
        case OprType::Delete: try {
            if (!m_formula) throw std::runtime_error("Formula list is not initialized");
            if (!m_formula->isEmpty()) {
                if (finish) {
                    finish = false;
                }
                else m_formula->removeLast();
                emit formulaChanged(*m_formula);
            }
            break;
        } catch (const std::exception &e) {
            qCritical() << "CalculateCore::Exception in formulalist: " << e.what();
            break;
        }
        case OprType::Clear: try {
            if (!m_formula) throw std::runtime_error("Formula list is not initialized");
            if (!m_formula->isEmpty()) {
                if (finish) finish = false;
                m_formula->clear();
                emit formulaChanged(*m_formula);
            }
            break;
        } catch (const std::exception &e) {
            qCritical() << "CalculateCore::Exception in formulalist: " << e.what();
            break;
        }
        case OprType::Calculate: {
            if (!m_formula->isEmpty()) {
                calculate();
                if (finish) emit calculateCompleted(m_result);
            }
            break;
        }
        default:qCritical() << "Unknown operation"; break;
    }
}

void CalculateCore::performMemOpr(const MemOprUnit &mem){
    switch (mem.memOpr) {
        case MemOpr::Clear: {
            memory->resetVar(mem.varName);
            break;
        }
        case MemOpr::Read: {
            InputUnit input_unit = InputUnit(mem.varName,InputType::Memory);
            if (finish || m_formula->isEmpty()) {
                m_result = memory->getVar(mem.varName);
                emit calculateCompleted(m_result);
            }
            appendToFormula(input_unit);
            break;
        }
        case MemOpr::Store: {
            if (finish) appendToFormula(InputUnit("Ans","R",InputType::Memory));
            if (!m_formula->isEmpty()) {
                calculate();
                if (finish) {
                    emit calculateCompleted(m_result);
                    QList<InputUnit> formula = *m_formula;
                    InputUnit m_unit = InputUnit();
                    m_unit.keyName.append("->");
                    m_unit.keyName.append(mem.varName);
                    memory->setVar(mem.varName, m_result);
                    formula.append(m_unit);
                    emit formulaChanged(formula);
                }
            }
            break;
        }
        case MemOpr::Add: {
            if (finish) appendToFormula(InputUnit("Ans","R",InputType::Memory));
            if (!m_formula->isEmpty()) {
                calculate();
                if (finish) {
                    emit calculateCompleted(m_result);
                    QList<InputUnit> formula = *m_formula;
                    InputUnit m_unit = InputUnit();
                    m_unit.keyName.append("M+");
                    calculate();
                    memory->memoryMuPlus(m_result);
                    formula.append(m_unit);
                    emit formulaChanged(formula);
                }
            }
            break;
        }
        case MemOpr::Substract: {
            if (finish) appendToFormula(InputUnit("Ans","R",InputType::Memory));
            if (!m_formula->isEmpty()) {
                calculate();
                if (finish) {
                    emit calculateCompleted(m_result);
                    QList<InputUnit> formula = *m_formula;
                    InputUnit m_unit = InputUnit();
                    m_unit.keyName.append("M-");
                    memory->memoryMuMinus(m_result);
                    formula.append(m_unit);
                    emit formulaChanged(formula);
                }
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
    if (!m_formula) throw std::runtime_error("Formula list is not initialized");
    QList<InputUnit> formula = *m_formula;
    formula.append(InputUnit("","#",InputType::Sign));
    QList<InputUnit>::iterator iterator = formula.begin();
    QStack<qreal> OPND;
    QStack<QChar> OPTR;
    QStack<QString> OPFC;

    OPTR.push('#');
    if (iterator == formula.end()) {
        qDebug() << "Empty formula";
        return;
    }
    if (iterator->keyValue == "+"|| iterator->keyValue == "-") {
        iterator->keyType = InputType::Digit;
    }
    while (iterator < formula.end()) {
        switch (iterator->keyType) {
            case InputType::Digit: {
                QString number;
                bool ok;
                while (iterator < formula.end() && iterator->keyType == InputType::Digit) {
                    number.append(iterator->keyValue);
                    ++iterator;
                }
                qreal m_num = number.toDouble(&ok);
                if (!ok) {
                    throw std::invalid_argument("Invalid number");
                }
                if (iterator->keyType == InputType::Suffix) {
                    m_num = Function::performSuffix(m_num, iterator->keyValue);
                    ++iterator;
                }
                OPND.push(m_num);
                if (iterator->keyType == InputType::Const || iterator->keyType == InputType::Memory || iterator->keyType == InputType::Function || iterator->keyValue == '(') {
                    iterator = formula.insert(iterator, InputUnit("","*", InputType::Sign));
                }
                break;
            }
            case InputType::Function: {
                OPFC.push(iterator->keyValue);
                OPTR.push('F');
                ++iterator;
                break;
            }
            case InputType::Const: {
                OPND.push(Function::getConst(iterator->keyValue));
                ++iterator;
                if (iterator->keyType == InputType::Const || iterator->keyType == InputType::Memory || iterator->keyType == InputType::Function || iterator->keyValue == '(') {
                    iterator = formula.insert(iterator, InputUnit("","*", InputType::Sign));
                }else if (iterator->keyType != InputType::Sign || iterator->keyValue == '(') {
                    --iterator;
                    throw std::invalid_argument("Invalid usage of constants");
                }
                break;
            }
            case InputType::Memory: {
                OPND.push(memory->getVar(iterator->keyValue));
                ++iterator;
                if (iterator->keyType == InputType::Const || iterator->keyType == InputType::Memory || iterator->keyType == InputType::Function || iterator->keyValue == '(') {
                    iterator = formula.insert(iterator, InputUnit("","*", InputType::Sign));
                }else if (iterator->keyType != InputType::Sign || iterator->keyValue == '(') {
                    --iterator;
                    throw std::invalid_argument("Invalid usage of variables");
                }
            }
            case InputType::Sign: {
                QChar priority = getPriority(OPTR.top(), iterator->keyValue.at(0));
                switch (priority.unicode()) {
                    case '>': {
                        if (OPND.size() < 2) throw std::invalid_argument("Continuous operators");
                        OPND.push(performCalculation(OPND.pop(), OPND.pop(), OPTR.pop()));
                        break;
                    }
                    case '<': {
                        OPTR.push(iterator->keyValue.at(0));
                        ++iterator;
                        if (iterator->keyValue == "+"|| iterator->keyValue == "-") {
                            iterator->keyType = InputType::Digit;
                        }
                        break;
                    }
                    case '=': {
                        if (OPTR.pop() == 'F') {
                            qreal funcValue = Function::performFormula(OPFC.pop(), OPND.pop());
                            OPND.push(funcValue);
                        }
                        ++iterator;
                        if (iterator->keyType == InputType::Const || iterator->keyType == InputType::Memory || iterator->keyType == InputType::Function || iterator->keyValue == '(') {
                            iterator = formula.insert(iterator, InputUnit("","*", InputType::Sign));
                        }
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
    qDebug() << "CalculateCore::Calculate completed";
    emit calculateCompleted(m_result);
    finish = true;
} catch (std::runtime_error &e) {
    qCritical() << "CalculateCore::Runtime error: " << e.what();
    exit(-1);
} catch (std::logic_error &e) {
    qCritical() << "CalculateCore::Logic error: " << e.what();
    emit errorOccurred(ErrorCode::Logic_error, e.what());
} catch (std::bad_alloc &e) {
    qCritical() << "CalculateCore::Bad alloc: " << e.what();
    emit errorOccurred(ErrorCode::Stack_error, e.what());
} catch (std::exception &e) {
    qCritical() << "CalculateCore::Unknown error: " << e.what();
    emit errorOccurred(ErrorCode::Other, e.what());
}
