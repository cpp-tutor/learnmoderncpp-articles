// cpp_assert.hpp : implement assert() macro in C++
// Version 2.0 2020/09/05, MIT license, (c) 2020 Richard Spencer

#ifndef cpp_assert_hpp
#define cpp_assert_hpp

#include <exception>
#include <iostream>
#include <string_view>

extern constexpr bool ReleaseBuild = false, AssertionsBuild = true;

template<typename T, typename E = std::exception>
inline void cpp_assert(T&& assertion, const E throwing = {}) {
    if constexpr (AssertionsBuild) {
        if (!assertion) {
            throw throwing;
        }
    }
}

template<typename T>
inline void log_assert(T&& assertion,
                        const std::string_view log_msg = {},
                        std::ostream& out = std::cerr,
                        const char *file = __FILE__,
                        const int line = __LINE__) {
    if constexpr (!ReleaseBuild) {
        if (!assertion) {
            out << file << '(' << line << "): *** assertion failed: " << log_msg << '\n';
        }
    }
}

#endif // cpp_assert_hpp