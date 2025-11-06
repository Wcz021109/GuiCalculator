#ifndef GUICALCULATOR_BUTTON_H
#define GUICALCULATOR_BUTTON_H

#include "unit.h"
#include <QObject>
#include <QPushButton>

class InputButton : public QPushButton {
    Q_OBJECT

public:
    explicit InputButton(const InputUnit &unit, QWidget* parent = nullptr);
    explicit InputButton(const QString &text, const InputUnit &unit, QWidget* parent = nullptr);
    ~InputButton() override;

    const InputUnit& getInputUnit() const;
    void setInputUnit(const InputUnit& unit);

private:
    InputUnit m_unit;
};

class OprButton : public QPushButton {
    Q_OBJECT

public:
    explicit OprButton(const QString &text, const OprUnit &unit, QWidget* parent = nullptr);
    ~OprButton() override;

    const OprUnit& getOprUnit() const;
    void setOprUnit(const OprUnit& unit);

private:
    OprUnit m_unit;
};

class MemButton : public QPushButton {
    Q_OBJECT

public:
    explicit MemButton(const MemOprUnit &unit, QWidget* parent = nullptr);
    explicit MemButton(const QString &text, const MemOprUnit &unit, QWidget* parent = nullptr);
    ~MemButton() override;

    const MemOprUnit& getMemOprUnit() const;
    void setMemOprUnit(const MemOprUnit& unit);

private:
    MemOprUnit m_unit;
};

#endif //GUICALCULATOR_BUTTON_H