#pragma once

#include <string>
#include <vector>
#include <complex>

struct Expression {
    std::string token;
    std::vector<Expression> args;
};

std::complex<double> eval(Expression& e);
