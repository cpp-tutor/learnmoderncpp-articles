// PhysicalProperty.hpp : define and use entities of basic SI Units
// requires -std=c++17 or later

#ifndef PhysicalProperty_hpp
#define PhysicalProperty_hpp

#include <iostream>
#include <cmath>

template<int M, int K, int S, typename T = double>
class PhysicalProperty {
    T scalar;
public:
    constexpr PhysicalProperty(const T& s)
        : scalar{ s } {}
    const T& get_scalar() const { return scalar; }
    const auto& operator+=(const PhysicalProperty<M,K,S,T>& rhs) {
        scalar += rhs.scalar;
        return *this;
    }
    const auto& operator-=(const PhysicalProperty<M,K,S,T>& rhs) {
        scalar -= rhs.scalar;
        return *this;
    }
    const auto& operator*=(const T& rhs) {
        scalar *= rhs;
        return *this;
    }
    const auto& operator/=(const T& rhs) {
        scalar /= rhs;
        return *this;
    }
};

template<int M, int K, int S, typename T>
auto operator+(const PhysicalProperty<M,K,S,T>& lhs, const PhysicalProperty<M,K,S,T>& rhs) {
    auto ret = lhs;
    ret += rhs;
    return ret;
}

template<int M, int K, int S, typename T>
auto operator-(const PhysicalProperty<M,K,S,T>& lhs, const PhysicalProperty<M,K,S,T>& rhs) {
    auto ret = lhs;
    ret -= rhs;
    return ret;
}

template<int M, int K, int S, typename T, int M1, int K1, int S1, typename T1>
auto operator*(const PhysicalProperty<M,K,S,T>& lhs, const PhysicalProperty<M1,K1,S1,T1>& rhs) {
    auto res = PhysicalProperty<M+M1, K+K1, S+S1, decltype(T{} * T1{})>(lhs.get_scalar() * rhs.get_scalar());
    return res;
}

template<int M, int K, int S, typename T, int M1, int K1, int S1, typename T1>
auto operator/(const PhysicalProperty<M,K,S,T>& lhs, const PhysicalProperty<M1,K1,S1,T1>& rhs) {
    auto res = PhysicalProperty<M-M1, K-K1, S-S1, decltype(T{} / T1{})>(lhs.get_scalar() / rhs.get_scalar());
    return res;
}

template<int M, int K, int S, typename T>
auto operator*(const T& lhs, const PhysicalProperty<M,K,S,T>& rhs) {
    auto res = rhs;
    res *= lhs;
    return res;
}   

template<int M, int K, int S, typename T>
auto operator/(const T& lhs, const PhysicalProperty<M,K,S,T>& rhs) {
    auto res = PhysicalProperty<-M,-K,-S>(lhs / rhs.get_scalar());
    return res;
}

template<int M, int K, int S, typename T>
auto sqrt(const PhysicalProperty<M,K,S,T>& pp) {
    static_assert((M % 2 == 0) && (K % 2 == 0) && (S % 2 == 0));
    auto res = PhysicalProperty<M/2, K/2, S/2, T>(sqrt(pp.get_scalar()));
    return res;
}

constexpr inline auto operator"" _scalar(const long double s) {
    return PhysicalProperty<0,0,0,double>(s);
}

constexpr inline auto operator"" _kilograms(const long double s) {
    return PhysicalProperty<0,1,0,double>(s);
}

constexpr inline auto operator"" _meters(const long double s) {
    return PhysicalProperty<1,0,0,double>(s);
}

constexpr inline auto operator"" _seconds(const long double s) {
    return PhysicalProperty<0,0,1,double>(s);
}

constexpr inline auto operator"" _Newtons(const long double s) {
    return PhysicalProperty<1,1,-2,double>(s);
}

constexpr inline auto operator"" _Joules(const long double s) {
    return PhysicalProperty<2,1,-2,double>(s);
}

constexpr inline auto operator"" _Watts(const long double s) {
    return PhysicalProperty<2,1,-3,double>(s);
}

template<int M, int K, int S, typename T>
std::ostream& operator<<(std::ostream& os, const PhysicalProperty<M,K,S,T>& pp) {
    os << pp.get_scalar() << ' ';
    if constexpr (M != 0) {
        os << 'm';
        if constexpr (M != 1) {
            os << M;
        }
    }
    if constexpr (K != 0) {
        os << "kg";
        if constexpr (K != 1) {
            os << K;
        }
    }
    if constexpr (S != 0) {
        os << 's';
        if constexpr (S != 1) {
            os << S;
        }
    }
    return os;
}

#endif // PhysicalProperty_hpp
