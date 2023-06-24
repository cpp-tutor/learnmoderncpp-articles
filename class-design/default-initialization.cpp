#include <string>

struct S1 {
    int i{};
    double d{};
    std::string s;
};

struct S2 {
    int i{ 1 };
    double d{ 2.3 };
    std::string s{ "Hello" };
};

class C1 {
    int i;
    double d;
    std::string s;
public:
    C1() : i{ 1 }, d{ 2.3 }, s{ "Hello" }
    {}
    C1(int i, double d, const std::string& s) : i{ i }, d{ d }, s{ s }
    {}
};

class C2 {
    int i{ 1 };
    double d{ 2.3 };
    std::string s{ "Hello" };
public:
    C2() = default;  // explicit generation of default constructor
    C2(int i, double d, const std::string& s) : i{ i }, d{ d }, s{ s }
    {}
};

class C3 {
    int i;
    double d;
    std::string s;
public:
    C3(int i = 1, double d = 2.3, const std::string& s = "Hello") : i{ i }, d{ d }, s{ s }
    {}
};
