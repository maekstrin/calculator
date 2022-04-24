#include <iostream>
#include "Parser.h"
#include "Expression.h"
#include <algorithm>

void test(const char *input, double expected) {
    try {
        Parser p;
        p.input = input;
        std::cout << input << std::endl;
        Expression exp = parse(p);
        std::complex<double> result = eval(exp);
        if (result == expected) return;
        std::cout << input << " = " << expected << " : error, got " << result << '\n';
    }
    catch (std::exception &e) {
        std::cout << input << " : exception: " << e.what() << '\n';
    }
}

void test_exps() {
    test("0", 0);
    test("1", 1);
    test("9", 9);
    test("10", 10);
    test("+1", 1);
    test("-1", -1);
    test("(1)", 1);
    test("(-1)", -1);
    test("1+20", 21);
    test("1 + 20", 21);
    test("1+20+300", 321);
    test("1+20+300+4000", 4321);
    test("-1+20", 19);
    test("--1+20", 21);
    test("---1+20", 19);
    test("(1+20)", 21);
    test("-2*3", -6);
    test("2*-3", -6);
    test("1++2", 3);
    test("1+10*2", 21);
    test("10*2+1", 21);
    test("(1+20)*2", 42);
    test("2*(1+20)", 42);
    test("(1+2)*(3+4)", 21);
    test("2*3+4*5", 26);
    test("100+2*10+3", 123);
    test("2^3", 8);
    test("2^3*5+2", 42);
    test("5*2^3+2", 42);
    test("2+5*2^3", 42);
    test("1+2^3*10", 81);
    test("2^3+2*10", 28);
    test("5 * 4 + 3 * 2 + 1", 27);
}

std::complex<double> process_input(std::vector<std::string> &inp) {
    Parser p;
    Parser::vars["e"] = "2.718281828";
    Parser::vars["PI"] = "3.1415926535";
    Parser::vars["j"] = "sqrt(-1)";
    for (int i = 0; i < inp.size(); ++i) {
        if (i != inp.size() - 1) {
            int ind = inp[i].find('=');
            std::string var_ = inp[i].substr(0, ind - 1);
            std::string exp_ = inp[i].substr(ind + 2, inp[i].length());
            p.input = exp_.c_str();
            Expression exp = parse(p);
            std::complex<double> result = eval(exp);
//            Parser::vars[var_] = std::to_string(result);

            Parser::vars[var_] = std::to_string(result.real()) + "+" + "i" + std::to_string(result.imag());

        } else {
            p.input = inp[i].c_str();
            Expression exp = parse(p);
            std::complex<double> result = eval(exp);
            return result;
        }
    }
}


int main() {
    std::string inp;
    std::vector<std::string> in;
    int n;
    std::cin >> n;
    std::getline(std::cin, inp);
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, inp);
        in.push_back(inp);
    }
//    std::reverse(in.begin(), in.end());
    std::cout << process_input(in);
}

