// simple.cpp : beginnings of class PhysicalProperty
// note: compile with -std=c++17 or later

#include <iostream>

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
};

template<int M, int K, int S, typename T>
auto operator+(const PhysicalProperty<M,K,S,T>& lhs, const PhysicalProperty<M,K,S,T>& rhs) {
    auto ret = lhs;
    ret += rhs;
    return ret;
}

template<int M, int K, int S, typename T, int M1, int K1, int S1, typename T1>
auto operator*(const PhysicalProperty<M,K,S,T>& lhs, const PhysicalProperty<M1,K1,S1,T1>& rhs) {
    PhysicalProperty<M+M1, K+K1, S+S1, decltype(T{} * T1{})> res{ lhs.get_scalar() * rhs.get_scalar() };
    return res;
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

int main() {
    auto time1 = PhysicalProperty<0,0,1>(20.0);
    auto time2 = PhysicalProperty<0,0,1>(10.0f);
    auto speed = PhysicalProperty<1,0,-1>(2.0);
    auto distance = speed * (time1 + time2);
    
    std::cout << "Speed " << speed << " for time " << (time1 + time2) << " is distance " << distance << '\n';
}
