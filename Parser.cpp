#include "Parser.h"
#include "Expression.h"
#include <string>
#include <cstring>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::string> Parser::vars;

int get_priority(const std::string &token) {
    if (token == "+") return 1;
    if (token == "-") return 1;
    if (token == "*") return 2;
    if (token == "/") return 2;
    if (token == "^") return 3;
    return 0;
}

std::string parse_token(Parser &parser) {
    while (std::isspace(*parser.input)) parser.input++;

    if (std::isdigit(*parser.input)) {
        std::string number;
        while (std::isdigit(*parser.input) || *parser.input == '.') {
            number.push_back(*parser.input);
            parser.input++;
        }
        return number;
    }
    for (std::string &s: parser.tokens) {
        if (std::strncmp(parser.input, s.c_str(), s.size()) == 0) {
            parser.input += s.size();
            return s;
        }
    }
    for (auto &s: parser.vars) {
        if (std::strncmp(parser.input, s.first.c_str(), s.first.size()) == 0) {
            parser.input += s.first.size();
            return s.second;
        }
    }
    return "";
}

Expression parse_simple_expression(Parser &parser) {
    std::string token = parse_token(parser);
    if (token.empty()) {
        std::cout << "You enter an invalid expression!" << std::endl;
        exit(1);
    }
    if (std::isdigit(token[0])) {
        Expression expression;
        expression.token = token;
        return expression;
    }

//    if (Parser::vars.find(token) != Parser::vars.end()) {
//        Expression expression;
//        expression.token = Parser::vars[token];
//        return expression;
//    }

    if (token == "(") {
        Expression parentheses_exp = parse(parser);
        if (parse_token(parser) != ")") {
            std::cout << "Invalid parentheses sequence" << std::endl;
            exit(1);
        } else {
            return parentheses_exp;
        }
    }

    Expression arg = parse_simple_expression(parser);
    Expression nested_exp;
    nested_exp.token = token;
    nested_exp.args = std::vector<Expression>();
    nested_exp.args.push_back(arg);
    return nested_exp;
}

Expression parse_binary_expression(Parser &parser, int min_priority) {
    Expression left_expression = parse_simple_expression(parser);
    while (true) {
        std::string operation = parse_token(parser);
        int priority = get_priority(operation);
        if (priority <= min_priority) {
            parser.input -= operation.size();
            return left_expression;
        }

        Expression right_expression = parse_binary_expression(parser, priority);
        std::vector<Expression> args = std::vector<Expression>();
        args.push_back(left_expression);
        args.push_back(right_expression);
        left_expression = Expression();
        left_expression.token = operation;
        left_expression.args = args;
    }
}

Expression parse(Parser &parser) {
    return parse_binary_expression(parser, 0);
}