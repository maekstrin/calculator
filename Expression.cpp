#include "Expression.h"
#include <cmath>
#include <iostream>
#include <cassert>



double eval(Expression &e) {
    if (e.args.size() == 2) {
        double a = eval(e.args[0]);
        double b = eval(e.args[1]);
        if (e.token == "+") {
            return a + b;
        }
        if (e.token == "-") {
            return a - b;
        }
        if (e.token == "*") {
            return a * b;
        }
        if (e.token == "/") {
            return a / b;
        }
        if (e.token == "^") {
            return pow(a, b);
        }
        std::cout << "Unknown binary operation" << std::endl;
    } else if (e.args.size() == 1) {
        double a = eval(e.args[0]);
        if (e.token == "-") {
            return -a;
        }
        if (e.token == "+") {
            return a;
        }
        if (e.token == "sin") {
            return sin(a);
        }
        if (e.token == "cos") {
            return cos(a);
        }
        if (e.token == "ln") {
            return log(a);
        }
        if (e.token == "sqrt") {
            return sqrt(a);
        }
        if (e.token == "exp") {
            return exp(a);
        }
        std::cout << "Unknown unary operation" << std::endl;
    } else if (e.args.size() == 0) {
        return strtod(e.token.c_str(), nullptr);
    }
    std::cout << "Unknown expression" << std::endl;
    exit(1);
}

