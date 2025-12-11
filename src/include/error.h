#ifndef GUICALCULATOR_ERROR_H
#define GUICALCULATOR_ERROR_H

enum class ErrorCode {
    Math_error = 1,
    Syntax_error = 2,
    Stack_error = -1,
    Logic_error = -2,
    Other = 0,
};



class calcException : public std::exception {
private:
    ErrorCode _code;
    std::string _msg;

public:
    calcException(ErrorCode code, std::string msg) : _code(code), _msg(msg) {}
    calcException(ErrorCode code) : _code(code) {}
    calcException(std::string msg) : _code(ErrorCode::Other), _msg(msg) {}
    calcException() : _code(ErrorCode::Other) {}

    const char* what() const noexcept override {
        const std::string text = "";
    }
};

#endif //GUICALCULATOR_ERROR_H