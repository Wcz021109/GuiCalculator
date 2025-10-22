#ifndef GUICALCULATOR_BUTTON_H
#define GUICALCULATOR_BUTTON_H

#include "unit.h"
#include <QPushButton>

class InputButton : public QPushButton {
    Q_OBJECT

public:
    explicit InputButton(const InputUnit &unit, QWidget* parent = nullptr):
        QPushButton(unit.keyName, parent),
        m_unit(unit){}
    explicit InputButton(const QString &text, const InputUnit &unit, QWidget* parent = nullptr):
        QPushButton(text, parent),
        m_unit(unit){}

    const InputUnit& getInputUnit() const {return m_unit;}
    void setInputUnit(const InputUnit& unit) {m_unit = unit;}

private:
    InputUnit m_unit;
};

class OprButton : public QPushButton {
    Q_OBJECT

public:
    explicit OprButton(const QString &text, const OprUnit &unit, QWidget* parent = nullptr):
        QPushButton(text, parent),
        m_unit(unit){}

    const OprUnit &getOprUnit() const {return m_unit;}
    void setOprUnit(const OprUnit& unit) {m_unit = unit;}

private:
    OprUnit m_unit;
};

class MemButton : public QPushButton {
    Q_OBJECT

public:
    explicit MemButton(const MemOprUnit &unit, QWidget* parent = nullptr):
        QPushButton(unit.varName, parent),
        m_unit(unit){}
    explicit MemButton(const QString &text, const MemOprUnit &unit, QWidget* parent = nullptr):
        QPushButton(text, parent),
        m_unit(unit){}

    const MemOprUnit& getMemOprUnit() const {return m_unit;}
    void setMemOprUnit(const MemOprUnit& unit) {m_unit = unit;}

private:
    MemOprUnit m_unit;
};

#endif //GUICALCULATOR_BUTTON_H