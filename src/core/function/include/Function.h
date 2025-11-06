#ifndef GUICALCULATOR_FUNCTION_H
#define GUICALCULATOR_FUNCTION_H
#include <QCoreApplication>

class Function{
public:
    explicit Function();
    ~Function();

    [[nodiscard]] static qreal getConst(const QString &constName);
    [[nodiscard]] static qreal performFormula(const QString &funcName, const qreal &base);
    [[nodiscard]] static qreal performSuffix(const qreal &base, const QString &suffix);

private:
    enum class Const;
    enum class Formula;
    enum class Suffix;

    static Const mapConst(const QString &constName);
    static Formula mapFormula(const QString &funcName);
    static Suffix mapSuffix(const QString &suffix);
};


#endif //GUICALCULATOR_FUNCTION_H