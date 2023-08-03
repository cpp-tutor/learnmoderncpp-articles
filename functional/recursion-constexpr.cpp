template<int N>
constexpr int factorial() {
    return N * factorial<N-1>();
}
 
template<>
constexpr int factorial<0>() {
    return 1;
}
 
static_assert(factorial<0>() == 1);
static_assert(factorial<5>() == 120);

constexpr unsigned long long factorial(unsigned long long n) {
    return (n < 2) ? 1 : n * factorial(n - 1);
}

static_assert(factorial(0) == 1);
static_assert(factorial(5) == 120);
