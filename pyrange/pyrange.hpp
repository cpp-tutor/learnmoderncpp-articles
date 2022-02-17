// pyrange.hpp : implement Python-style range class to use with range-for statement
// requires std=c++17 or later

#include <stdexcept>

template<typename T = int>
class pyrange {
    struct end_range {
        T e;
    };
    struct begin_range {
        T b, s;
        begin_range& operator++() { b += s; return *this; }
        bool operator!=(const end_range& c) const
            { return (s < 0) ? b > c.e : b < c.e; }
        const T& operator*() const { return b; }
    };
    begin_range br;
    end_range er;
public:
    explicit pyrange(T arg_e) : br{ 0, 1 }, er{ arg_e } {}
    explicit pyrange(T arg_b, T arg_e, T arg_s = 1) : br{ arg_b, arg_s }, er{ arg_e }
    { if (!arg_s) throw std::out_of_range{"pyrange: step must be non-zero"}; }
    auto& begin() { return br; }
    auto& end() { return er; }
};
