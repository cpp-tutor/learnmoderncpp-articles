template<long long N>
struct is_odd {
    static const bool value = is_odd<N-2>::value;
};

template<long long N>
constexpr bool is_odd_v = is_odd<N>::value;

template<>
struct is_odd<1> {
    static const bool value = true;
};

template<>
struct is_odd<0> {
    static const bool value = false;
};

static_assert(is_odd_v<3> == true);
static_assert(is_odd_v<4> == false);
