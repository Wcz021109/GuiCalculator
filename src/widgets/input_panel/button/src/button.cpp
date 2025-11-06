#include "button.h"

InputButton::InputButton(const InputUnit &unit, QWidget* parent):
        QPushButton(unit.keyName, parent),
        m_unit(unit){}

InputButton::InputButton(const QString &text, const InputUnit &unit, QWidget* parent):
        QPushButton(text, parent),
        m_unit(unit){}

InputButton::~InputButton() = default;

const InputUnit& InputButton::getInputUnit() const {return m_unit;}

void InputButton::setInputUnit(const InputUnit& unit) {m_unit = unit;}


OprButton::OprButton(const QString &text, const OprUnit &unit, QWidget* parent):
        QPushButton(text, parent),
        m_unit(unit){}

OprButton::~OprButton() = default;


const OprUnit& OprButton::getOprUnit() const {return m_unit;}

void OprButton::setOprUnit(const OprUnit& unit) {m_unit = unit;}


MemButton::MemButton(const MemOprUnit &unit, QWidget* parent):
        QPushButton(unit.varName, parent),
        m_unit(unit){}

MemButton::MemButton(const QString &text, const MemOprUnit &unit, QWidget* parent):
        QPushButton(text, parent),
        m_unit(unit){}

MemButton::~MemButton() = default;

const MemOprUnit& MemButton::getMemOprUnit() const {return m_unit;}

void MemButton::setMemOprUnit(const MemOprUnit& unit) {m_unit = unit;}