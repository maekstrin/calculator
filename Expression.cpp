#include "Expression.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <complex>


std::complex<double> eval(Expression &e) {
    if (e.args.size() == 2) {
        std::complex<double> a = eval(e.args[0]);
        std::complex<double> b = eval(e.args[1]);
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
        std::complex<double> a = eval(e.args[0]);
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
            return (a.real() >= 0 ? sqrt(a) : -sqrt(a));
        }
        if (e.token == "exp") {
            return exp(a);
        }
        if (e.token == "real"){
            return a.real();
        }
        if (e.token == "imag"){
            return a.imag();
        }
        if (e.token == "mag"){
            return abs(a);
        }
        if (e.token == "phase"){
            return arg(a);
        }
        if (e.token == "j"){
            std::complex<double> num(a.imag(), a.real());
            return num;
        }
        std::cout << "Unknown unary operation" << std::endl;
    } else if (e.args.size() == 0) {
        return strtod(e.token.c_str(), nullptr);
    }
    std::cout << "Unknown expression" << std::endl;
    exit(1);
}

