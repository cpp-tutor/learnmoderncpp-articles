#ifndef Traits_hpp
#define Traits_hpp

#include <type_traits>

template <typename T, typename U = void>
struct AccumulateTypeTraits {
    using Type = U;
};

template <typename T>
struct AccumulateTypeTraits<T, typename std::enable_if_t<std::is_integral_v<T> && std::is_unsigned_v<T>>> {
    using Type = unsigned long long;
};

template <typename T>
struct AccumulateTypeTraits<T, typename std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>>> {
    using Type = long long;
};

template <typename T>
struct AccumulateTypeTraits<T, typename std::enable_if_t<std::is_floating_point_v<T>>> {
    using Type = T;
};

#endif // Traits_hpp
