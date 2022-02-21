// factorial-tmp.cpp : calculate factorial value using TMP

#include <cstdlib>

template<std::size_t N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template<> // specialization must appear after generic declaration or definition
struct Factorial<0> {
    static const int value = 1;
};

static_assert(Factorial<5>::value == 120);
