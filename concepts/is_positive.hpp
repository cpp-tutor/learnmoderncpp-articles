template<typename T, T N>
constexpr bool is_positive() {
    return N > T{};
}

static_assert(is_positive<int,3>());
static_assert(!is_positive<unsigned,0>());
static_assert(!is_positive<int,-1>());
