#pragma once

#include <string>
#include <vector>

struct Expression {
    std::string token;
    std::vector<Expression> args;
};

double eval(Expression& e);
