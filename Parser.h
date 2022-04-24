#pragma once

#include <string>
#include "Expression.h"
#include <vector>
#include <unordered_map>

struct Parser {
    static std::unordered_map<std::string, std::string> vars;
    const char *input;
    std::vector<std::string> tokens = {"+", "-", "^", "*", "/",
                                       "mod", "abs", "sin", "cos", "(", ")",
                                       "ln", "sqrt", "exp", "real", "imag", "mag", "phase", "j"};
};

std::string parse_token(Parser &parser);

Expression parse_simple_expression(Parser &parser);

Expression parse_binary_expression(Parser &parser, int min_priority);

Expression parse(Parser &parser);
