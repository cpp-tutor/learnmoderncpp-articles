#ifndef CircularArray_hpp
#define CircularArray_hpp

#include <bitset>
#include <stdexcept>

template<typename T,std::size_t N>
class CircularArray final {
    T data[N];
    std::bitset<N> inUse;
    std::size_t next{};
    void doNext() {
        ++next;
        next %= N;
    }
public:
    CircularArray() = default;
    CircularArray(const T* ptr, std::size_t n) {
        for (auto *p = ptr; p != ptr + n; ++p) {
            data[next] = *p;
            inUse[next] = true;
            doNext();
        }
    }
    CircularArray(const CircularArray&) = default;
    CircularArray(CircularArray&&) = default;
    CircularArray& operator=(const CircularArray&) = default;
    CircularArray& operator=(CircularArray&&) = default;
    CircularArray& operator=(const T& rhs) {
        data[next] = rhs;
        inUse[next] = true;
        return *this;
    }
    CircularArray& operator=(T&& rhs) {
        data[next] = std::move(rhs);
        inUse[next] = true;
        return *this;
    }
    CircularArray& operator=(nullptr_t) {
        data[next] = T{};
        inUse[next] = false;
        return *this;
    }
    bool hasData() const {
        return inUse[next];
    }
    const T& operator*() const {
        if (!hasData()) {
            throw std::runtime_error("No data");
        }
        return data[next];
    }
    const T* operator->() const {
        return &(operator*());
    }
    std::size_t operator++() {
        doNext();
        return next;
    }
    std::size_t operator++(int) {
        auto prev = next;
        doNext();
        return prev;
    }
    std::size_t operator--() {
        --next;
        if (next >= N) {
            next = N - 1;
        }
        return next;
    }
    std::size_t operator--(int) {
        auto prev = next;
        operator--();
        return prev;
    }
};

#endif