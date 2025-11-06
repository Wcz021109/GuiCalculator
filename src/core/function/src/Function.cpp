#include "Function.h"

#include <QMap>
#include <complex>
#include <QDebug>

Function::Function() {}

Function::~Function() {}

enum class Function::Const {
    PI,
    EXP
};

Function::Const Function::mapConst(const QString &constName){
    QMap<QString,Const> constMap{
        {"PI",Const::PI},
        {"EXP",Const::EXP}
    };
    return constMap[constName];
}

qreal Function::getConst(const QString &constName){
    switch (mapConst(constName)) {
        case Const::PI: return 3.14159265358979323846;
        case Const::EXP: return std::exp(1);
        default:return 0;
    }
}

enum class Function::Formula {
    abs, recp, sqrt,
    log, ln, exp,
    sin, cos, tan,
    asin, acos, atan,
    sinh, cosh, tanh,
    asinh, acosh, atanh,
};

Function::Formula Function::mapFormula(const QString &funcName) {
    QMap<QString,Formula> FormulaMap{
        {"abs(",Formula::abs},{"recp(",Formula::recp},{"sqrt(",Formula::sqrt},
        {"log(",Formula::log},{"ln(",Formula::ln},{"exp(",Formula::exp},
        {"sin(",Formula::sin},{"cos(",Formula::cos},{"tan(",Formula::tan},
        {"asin(",Formula::asin},{"acos(",Formula::acos},{"atan(",Formula::atan},
        {"sinh(",Formula::sinh},{"cosh(",Formula::cosh},{"tanh(",Formula::tanh},
        {"asinh(",Formula::asinh},{"acosh(",Formula::acosh},{"atanh(",Formula::atanh}
    };
    return FormulaMap[funcName];
}

qreal Function::performFormula(const QString &funcName, const qreal &base){
    switch (mapFormula(funcName)) {
        case Formula::abs: return std::abs(base);
        case Formula::recp: return 1/base;
        case Formula::sqrt: return std::sqrt(base);
        case Formula::log: return std::log10(base);
        case Formula::ln: return std::log(base);
        case Formula::exp: return std::exp(base);
        case Formula::sin: return std::sin(base);
        case Formula::cos: return std::cos(base);
        case Formula::tan: return std::tan(base);
        case Formula::asin: return std::asin(base);
        case Formula::acos: return std::acos(base);
        case Formula::atan: return std::atan(base);
        case Formula::sinh: return std::sinh(base);
        case Formula::cosh: return std::cosh(base);
        case Formula::tanh: return std::tanh(base);
        case Formula::asinh: return std::asinh(base);
        case Formula::acosh: return std::acosh(base);
        case Formula::atanh: return std::atanh(base);
        default: return 0;
    }
}

enum class Function::Suffix {
    Square,
    Cubic,
    Percentage,
};

Function::Suffix Function::mapSuffix(const QString &suffix) {
    QMap<QString,Suffix> suffixMap{
        {"^2",Suffix::Square},{"^3",Suffix::Cubic},
        {"%",Suffix::Percentage}
    };
    return suffixMap[suffix];
}

qreal Function::performSuffix(const qreal &base, const QString &suffix){
    switch (mapSuffix(suffix)) {
        case Suffix::Square: return base * base;
        case Suffix::Cubic: return base * base * base;
        case Suffix::Percentage: return base * 0.01;
        default: return 0;
    }
}