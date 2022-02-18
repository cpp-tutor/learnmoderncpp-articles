// rpn-calc-printer.cpp : convert an infix expression to reverse polish notation
// note: from bash, run with eg. '$ echo "2+3*9-1" | ./rpn-calc-printer'

#include <iostream>
#include <cctype>

using std::cout;
using std::cerr;
using std::cin;
using std::istream;
using std::ostream;

using Number = double;

enum class Op : char {
    add = '+',
    subtract = '-',
    multiply = '*',
    divide = '/',
    number = '.',
    none = '\0'
};

class StackMachine {
public:
    virtual ~StackMachine() = default;
    virtual void apply_operator(Op op) = 0;
    virtual void push_number(Number n) = 0;
};

class StackPrinter final : public StackMachine {
    ostream& out;
public:
    StackPrinter(ostream& os = cout) : out{os} {}
    virtual ~StackPrinter() {
        out << '\n';
    }
    virtual void apply_operator(Op op) override {
        out << ' ' << static_cast<char>(op);
    }
    virtual void push_number(Number n) override {
        out << ' ' << n;
    }
};

struct Symbol {
    Op sym;
    Number num;
};

class ExpressionEvaluator {
    Symbol lookahead;
    istream& in;
    StackMachine& target;
    void next();
    void term();
    void factor();
public:
    ExpressionEvaluator(StackMachine& sm, istream& is = cin)
        : target{sm}, in{is} { next(); }
    void expression();
};

int main() {
    StackPrinter sp;
    ExpressionEvaluator eval(sp);
    eval.expression();
}

void ExpressionEvaluator::next() {
    char c{};
    in >> c;
    if (isdigit(c) || (c == '.')) {
        in.unget();
        in >> lookahead.num;
        lookahead.sym = Op::number;
    }
    else {
        lookahead.num = Number{};
        lookahead.sym = static_cast<Op>(c);
    }
}

void ExpressionEvaluator::expression() {
    term();
    while ((lookahead.sym == Op::add) || (lookahead.sym == Op::subtract)) {
        Op op{ lookahead.sym };
        next();
        term();
        target.apply_operator(op);
    }
}

void ExpressionEvaluator::term() {
    factor();
    while ((lookahead.sym == Op::multiply) || (lookahead.sym == Op::divide)) {
        Op op{ lookahead.sym };
        next();
        factor();
        target.apply_operator(op);
    }
}

void ExpressionEvaluator::factor() {
    if (lookahead.sym == Op::number) {
        target.push_number(lookahead.num);
        next();
    }
    else {
        cerr << "Unknown operator: "
            << static_cast<char>(lookahead.sym) << '\n';
    }
}
