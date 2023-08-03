#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>
 
template<typename R, typename P>
class Memoizer {
    constexpr R f(const P& n) {
        if (n < 2) {
            return n;
        }
        else {
            return call(n - 2) + call(n - 1);
        }
    }
    std::unordered_map<P,R> m;
public:
    R call(const P& param) {
        if (auto iter = m.find(param); iter != m.end()) {
            return iter->second;
        }
        else {
            auto r = f(param);
            m.insert({ param, r });
            return r;
        }
    }
};
 
int main(const int argc, const char **argv) {
    Memoizer<long long,long long> m;
    if (argc == 2) {
        auto n = std::stoll(argv[1]);
        std::cout << "Fibonacci(" << n << "): " << m.call(n) << '\n';
    }
    else {
        for (long long n = 0; n != 50; ++n) {
            std::cout << "Fibonacci(" << n << "): " << m.call(n) << '\n';
        }
    }
}
