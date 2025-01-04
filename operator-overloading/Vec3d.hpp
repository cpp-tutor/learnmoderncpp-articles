#ifndef Vec3d_hpp
#define Vec3d_hpp

#include <numeric>
#include <ostream>

template<typename T = double>
requires(!std::is_integral_v<T>)
class Vec3d final {
    T data[3];
public:
    Vec3d() {
        data[0] = data[1] = data[2] = T{0};
    }
    Vec3d(const T& x, const T& y, const T& z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
    Vec3d(const Vec3d& rhs) = default;
    Vec3d& operator=(const Vec3d& rhs) = default;
    Vec3d(Vec3d&& rhs) = default;
    Vec3d& operator=(Vec3d&& rhs) = default;
    const T& x() const { return data[0]; }
    const T& y() const { return data[1]; }
    const T& z() const { return data[2]; }
    Vec3d& operator+=(const Vec3d& rhs) {
        data[0] += rhs.data[0];
        data[1] += rhs.data[1];
        data[2] += rhs.data[2];
        return *this;
    }
    Vec3d& operator-=(const Vec3d& rhs) {
        data[0] -= rhs.data[0];
        data[1] -= rhs.data[1];
        data[2] -= rhs.data[2];
        return *this;
    }
    Vec3d& operator*=(const T& rhs) {
        data[0] *= rhs;
        data[1] *= rhs;
        data[2] *= rhs;
        return *this;
    }
    Vec3d& operator/=(const T& rhs) {
        return operator*=(T{1} / rhs);
    }
    Vec3d operator-() const {
        return Vec3d(-data[0], -data[1], -data[2]);
    }
    T dot(const Vec3d& rhs) const {
        return std::inner_product(std::begin(data), std::end(data), std::begin(rhs.data), T{0});
    }
    Vec3d cross(const Vec3d& rhs) const {
        return Vec3d(data[1] * rhs.data[2] - data[2] * rhs.data[1],
            data[2] * rhs.data[0] - data[0] * rhs.data[2],
            data[0] * rhs.data[1] - data[1] * rhs.data[0]);
    }
};

template<typename T>
inline Vec3d<T> operator+(const Vec3d<T>& lhs, const Vec3d<T>& rhs) {
    return Vec3d<T>(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

template<typename T>
inline Vec3d<T> operator-(const Vec3d<T>& lhs, const Vec3d<T>& rhs) {
    return Vec3d<T>(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

template<typename T>
inline Vec3d<T> operator*(const Vec3d<T>& lhs, const T& rhs) {
    return Vec3d<T>(lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs);
}

template<typename T>
inline Vec3d<T> operator*(const T& lhs, const Vec3d<T>& rhs) {
    return operator*(rhs, lhs);
}

template<typename T>
inline Vec3d<T> operator/(const Vec3d<T>& lhs, const T& rhs) {
    return Vec3d<T>(lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec3d<T>& obj) {
    return os << '(' << obj.x() << ',' << obj.y() << ',' << obj.z() << ')';
}

#endif