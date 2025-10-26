#include "CalculateCore.h"
#include <QStack>
#include <QMap>
#include <QDebug>
#include <bits/regex_error.h>

CalculateCore::CalculateCore(QObject *parent):
    QObject(parent) {
    try {
        m_formula = new QList<InputUnit>();
        m_iterator = m_formula->end();
        m_result = 0;
    }catch (std::exception &e) {
        qCritical() << "CalculateCore::Initialization failed: " << e.what();
        exit(-1);
    }
    iniAutoClear();
}

CalculateCore::~CalculateCore() {
    delete m_formula;
    exit(0);
}

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
            emit autoClearFormula();
            finish = false;
        }
        if (!m_formula) throw std::runtime_error("Formula list is not initialized");
        m_formula->append(formula);
        emit formulaChanged(*m_formula);
    }    catch (const std::exception &e) {
        qCritical() << "CalculateCore::Exception in formulalist: " << e.what();
    }
}

void CalculateCore::deleteFromFormula() {
    if (!m_formula->isEmpty()) {
        m_formula->removeLast();
        emit formulaChanged(*m_formula);
    }
}

void CalculateCore::clearFormula() {
    if (!m_formula->isEmpty()) {
        m_formula->clear();
        emit formulaChanged(*m_formula);
    }
}

void CalculateCore::do_calculate() {
    if (!m_formula->isEmpty()) {
        m_formula->append(InputUnit("#","#",InputType::Sign));
        try {
            calculate();
            qDebug() << "CalculateCore::Calculate completed";
            emit calculateCompleted(m_result);
        }catch (const std::bad_alloc &e) {
            qDebug() << "CalculateCore::Calculate failed: " << e.what();
            emit errorOccurred(ErrorCode::Stack_error, InputUnit(), e.what());
        }catch (std::overflow_error &e) {
            qDebug() << "CalculateCore::Calculate failed: " << e.what();
            emit errorOccurred(ErrorCode::Stack_error, InputUnit(), e.what());
        }catch (std::out_of_range &e) {
            qDebug() << "CalculateCore::Calculate failed: " << e.what();
            emit errorOccurred(ErrorCode::Stack_error, InputUnit(), e.what());
        }catch (std::invalid_argument &e) {
            qDebug() << "CalculateCore::Calculate failed: " << e.what();
            emit errorOccurred(ErrorCode::Invalid_argument, *m_iterator ,e.what());
        }catch (std::domain_error &e) {
            qDebug() << "CalculateCore::Calculate failed: " << e.what();
            emit errorOccurred(ErrorCode::Domain_error, *m_iterator,e.what());
        }catch (std::logic_error &e) {
            qDebug() << "CalculateCore::Calculate failed: " << e.what();
            emit errorOccurred(ErrorCode::Logic_error, *m_iterator,e.what());
        }catch (std::exception &e) {
            qDebug() << "CalculateCore::Calculate failed: " << e.what();
            emit errorOccurred(ErrorCode::Other, InputUnit() ,e.what());
        }
        m_formula->removeLast();
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

void CalculateCore::calculate() {
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
                    //OPND.push(Memory::operateSuffix(m_num))
                    OPND.push(m_num);
                    ++m_iterator;
                } else OPND.push(m_num);
                break;
            }
            case InputType::Function: {
                OPFC.push(m_iterator->keyValue);
                OPTR.push('F');
                ++m_iterator;
                break;
            }
            case InputType::Const: {
                //OPND.push(Function::searchConst(opConst))
                ++m_iterator;
                if (m_iterator->keyType != InputType::Sign || m_iterator->keyValue == '(') {
                    --m_iterator;
                    throw std::invalid_argument("Invalid usage of constants");
                }
                break;
            }
            case InputType::Sign: {
                QChar priority = getPriority(OPTR.top(), m_iterator->keyValue.at(0));
                switch (priority.unicode()) {
                    case '>': {
                        if (OPND.size() < 2) throw std::invalid_argument("Continuous operators");
                        qreal b = OPND.pop();
                        qreal a = OPND.pop();
                        QChar t = OPTR.pop();
                        qreal r = 0;
                        r = performCalculation(a, b, t);
                        qDebug() << a << t << b << '=' << r;
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
                            OPFC.pop();
                        }
                        ++m_iterator;
                        break;
                    }
                    case '!': throw std::invalid_argument("Invalid usage of operator");
                    default: throw std::invalid_argument("Unrecognized operator");
                }
            break;
            }
            default: throw std::invalid_argument("Unrecogznized input");
        }
    }
    if (OPND.isEmpty()) throw std::invalid_argument("Empty formula");
    m_result = OPND.top();
    qDebug() << "Result: " << m_result;
    finish = true;
    return;
}

void CalculateCore::iniAutoClear() {
    //connect(this, SIGNAL(autoAppendAns()), this, SLOT(appendToFormula()));
    connect(this,SIGNAL(autoClearFormula()),this,SLOT(clearFormula()));
}
