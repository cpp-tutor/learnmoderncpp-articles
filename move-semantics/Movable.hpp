#ifndef Movable_hpp
#define Movable_hpp

#include <iostream>
#include <cstdint>
#include <cstring>

class Movable {
    char *str;
    const std::size_t id;
    inline static std::size_t index{};
    inline static std::ostream& os = std::cerr;
    char *dup(const char *s1) {
        auto len = strlen(s1);
        auto s2 = new char[len + 1];
        memcpy(s2, s1, len + 1);
        return s2;
    }
public:
    Movable() : str{ nullptr }, id{ ++index } {
        os << "Construct empty Movable with id " << id << '\n';
    }
    Movable(const char *s) : str{ dup(s) }, id{ ++index } {
        os << "Construct Movable with id " << id << " and content: " << str << '\n';
    }
    Movable(const Movable& rhs) : str{ dup(rhs.str) }, id{ ++index } {
        os << "Copy-construct Movable with id " << id << " from id " << rhs.id << '\n';
    }
    Movable(Movable&& rhs) : str{ rhs.str }, id{ ++index } {
        rhs.str = nullptr;
        os << "Move-construct Movable with id " << id << " from id " << rhs.id << '\n';
    }
    Movable& operator=(const Movable& rhs) {
        delete[] str;
        str = dup(rhs.str);
        os << "Copy-assign Movable with id " << id << " from id " << rhs.id << '\n';
        return *this;
    }
    Movable& operator=(Movable&& rhs) {
        delete[] str;
        str = rhs.str;
        rhs.str = nullptr;
        os << "Move-assign Movable with id " << id << " from id " << rhs.id << '\n';
        return *this;
    }
    ~Movable() { delete[] str; }
    void print(std::ostream& out = std::cout) {
        out << id << ": ";
        if (str) {
            out << str << '\n';
        }
        else {
            out << "(No data)\n";
        }
    }
};

#endif // Movable_hpp