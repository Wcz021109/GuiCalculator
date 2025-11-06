#ifndef GUICALCULATOR_UNIT_H
#define GUICALCULATOR_UNIT_H

#include <QString>

enum class InputType {
    Digit = 1,
    Sign = 2,
    Const = 3,
    Function = 4,
    Suffix = 5,
    Operation = -1,
    Memory = -2,
    Other = 0
};

enum class OprType {
    Calculate = 1,
    Delete = 2,
    Clear = 3,
    Other = 0,
};

enum class MemOpr {
    Read = 1,
    Store = 2,
    Add = 3,
    Substract = 4,
    Clear = 5,
    Other = 0,
};

struct InputUnit {
    QString keyName;
    QString keyValue;
    InputType keyType;

    InputUnit (const QString &name, const QString &value, const InputType &type)
        : keyName(name), keyValue(value), keyType(type) {}
    InputUnit (const QString &nmvl, const InputType &type)
        : keyName(nmvl), keyValue(nmvl), keyType(type) {}
    InputUnit ()
        : keyName(""), keyValue(""), keyType(InputType::Other) {}

};

struct OprUnit {
    OprType opr;
    InputType keyType = InputType::Operation;
    OprUnit (const OprType &type)
        : opr(type), keyType(InputType::Operation) {}
    OprUnit ()
        : opr(OprType::Other), keyType(InputType::Operation) {}
};

struct MemOprUnit {
    QChar varName;
    MemOpr memOpr;
    InputType keyType = InputType::Memory;
    MemOprUnit (const QChar &var, const MemOpr &type)
        : varName(var), memOpr(type), keyType(InputType::Memory) {}
    MemOprUnit ()
        : varName(0), memOpr(MemOpr::Other), keyType(InputType::Memory) {}
};

#endif //GUICALCULATOR_UNIT_H