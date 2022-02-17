// case_string.hpp : allow string literals as case labels, -std=c++17
// Version 1.4: 2022/01/15, MIT license, (c) 2020-22 Richard Spencer

#ifndef case_string_hpp
#define case_string_hpp

#include <string_view>

inline constexpr auto hash_djb2a(const std::string_view sv) {
    unsigned long hash{ 5381 };
    for (unsigned char c : sv) {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

inline constexpr auto operator"" _sh(const char *str, size_t len) {
    return hash_djb2a(std::string_view{ str, len });
}

#endif // case_string_hpp