#ifndef GUICALCULATOR_ERRORCODE_H
#define GUICALCULATOR_ERRORCODE_H

enum class ErrorCode {
    Domain_error = 1,
    Invalid_argument = 2,
    Stack_error = -1,
    Logic_error = -2,
    Other = 0,
};

#endif //GUICALCULATOR_ERRORCODEH