#ifndef GUICALCULATOR_INIEMUMSTRUCT_H
#define GUICALCULATOR_INIEMUMSTRUCT_H

#include <QString>

enum class InputType {
    Digit = 1,
    Sign = 2,
    Const = 3,
    Function = 4,
    Suffix = 5,
    Other = 0
};

struct InputUnit {
    QString keyName;
    QString keyValue;
    InputType keyType;

    InputUnit (const QString &keyName, const QString &keyValue, const InputType &keyType)
        : keyName(keyName), keyValue(keyValue), keyType(keyType) {}
};

enum class ErrorCode {
    Math_error = 1,
    Syntax_error = 2,
    Stack_error = 3,
    Dev_error = 4,
    Other = 0,
};

#endif //GUICALCULATOR_INIEMUMSTRUCT_H