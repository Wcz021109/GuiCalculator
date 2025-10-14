#include "CalculateCore.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

bool runtest(CalculateCore &calculator, const QString &expression, QString &result) {
    calculator.setFormula(expression);
    calculator.calculate();

    if (calculator.error().isEmpty()) {
        result = calculator.result();
        return true;
    }else {
        result = calculator.error();
        return false;
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    CalculateCore calculator;
    std::string input;
    QString result;

    qDebug() << "Calculation Core Test";
    qDebug() << "----------------------";
    qDebug() << "Commands:";
    qDebug() << "  [expression] - Calculate expression";
    qDebug() << "  clear        - Clear formula";
    qDebug() << "  show         - Show current formula";
    qDebug() << "  quit         - Exit program";
    qDebug() << "----------------------";

    while (true) {
        std::cout << ">";
        std::cin >> input;
        QString expression = QString::fromStdString(input);
        if (expression == "clear") {
            calculator.clear();continue;
        }else if (expression == "show") {
            qDebug() << calculator.formula();continue;
        }else if (expression == "quit") {
            break;
        }else {
            expression.append("#");
            if (runtest(calculator,expression,result)) {
                std::cout << "= " << result.toStdString() << std::endl;continue;
            }else{
                std::cerr << "[ERROR] " << result.toStdString() << std::endl;continue;
            }
        }
    }
    return 0;
}