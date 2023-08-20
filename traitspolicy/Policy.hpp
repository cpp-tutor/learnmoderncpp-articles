#ifndef Policy_hpp
#define Policy_hpp

struct SummationPolicy {
    inline const static int init{};

    template<typename T,typename U>
    inline static void operation(T& s, const U& v) {
        s += v;
    }
};

struct MultiplicationPolicy {
    inline const static int init{ 1 };

    template<typename T,typename U>
    inline static void operation(T& s, const U& v) {
        s *= v;
    }
};

#endif // Policy_hpp
