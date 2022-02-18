// rpn-calc-evaluate.cpp : evaluate an infix expression using reverse polish notation

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

using std::cout;
using std::cerr;
using std::cin;
using std::istream;
using std::ostream;
using std::stack;
using std::string;
using std::istringstream;

using Number = double;

enum class Op : char {
    add = '+',
    subtract = '-',
    multiply = '*',
    divide = '/',
    exponent = '^',
    uminus = '_',
    left = '(',
    right = ')',
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

class StackCalculator final : public StackMachine {
    stack<Number> stk;
    ostream& out;
public:
    StackCalculator(ostream& os = cout) : out{os} {}
    virtual ~StackCalculator() {
        out << "=> " << stk.top() << '\n';
    }
    virtual void apply_operator(Op op) override {
        if (stk.size() < 2) {
            cerr << "number expected\n";
            return;
        }
        Number b = stk.top();
        stk.pop();
        Number a = stk.top();
        stk.pop();
        switch (op) {
            case Op::add:
                stk.push(a + b);
                break;
            case Op::subtract:
                stk.push(a - b);
                break;
            case Op::multiply:
                stk.push(a * b);
                break;
            case Op::divide:
                if (b) {
                    stk.push(a / b);
                }
                else {
                    cerr << "divide by zero\n";
                }
                break;
            case Op::exponent:
                stk.push(pow(a, b));
                break;
            case Op::uminus:
                stk.push(-b);
                break;
            default:
                cerr << "unknown operator: "
                    << static_cast<char>(op) << '\n';
                break;
        }
    }
    virtual void push_number(Number n) override {
        stk.push(n);
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
    void negative();
    void index();
    void factor();
public:
    ExpressionEvaluator(StackMachine& sm, istream& is = cin)
        : target{sm}, in{is} { next(); }
    void expression();
};

int main() {
    for (;;) {
        string input;
        getline(cin, input);
        if (input.empty()) {
            break;
        }
        {
            istringstream strm{ input };
            StackPrinter sp;
            ExpressionEvaluator eval1(sp, strm);
            eval1.expression();
        }
        {
            istringstream strm{ input };
            StackCalculator sc;
            ExpressionEvaluator eval2(sc, strm);
            eval2.expression();
        }
    }
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
    negative();
    while ((lookahead.sym == Op::multiply) || (lookahead.sym == Op::divide)) {
        Op op{ lookahead.sym };
        next();
        negative();
        target.apply_operator(op);
    }
}

void ExpressionEvaluator::negative() {
    if (lookahead.sym == Op::uminus) {
        target.push_number(Number{});
        next();
        index();
        target.apply_operator(Op::uminus);
    }
    else {
        index();
    }
}

void ExpressionEvaluator::index() {
    factor();
    if (lookahead.sym == Op::exponent) {
        next();
        negative();
        target.apply_operator(Op::exponent);
    }
}

void ExpressionEvaluator::factor() {
    if (lookahead.sym == Op::number) {
        target.push_number(lookahead.num);
        next();
    }
    else if (lookahead.sym == Op::left) {
        next();
        expression();
        if (lookahead.sym != Op::right) {
            cerr << "missing )\n";
        }
        next();
    }
    else {
        cerr << "\nunknown operator: "
            << static_cast<char>(lookahead.sym) << '\n';
    }
}
