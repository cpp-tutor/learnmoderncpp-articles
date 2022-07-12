// return_value.cpp : allow a coroutine to return a dynamically calculated value
// to compile use: /std:c++latest (Visual Studio 2022)
//                 -std=c++20 (g++)
//                 -std=c++20 -stdlib=libc++ (clang++)

#if defined(__clang__) && (__clang_major__ < 14) // workaround
#include <experimental/coroutine>

namespace std {
    using namespace experimental;
}
#else
#include <coroutine>
#endif
#include <iostream>

template<typename T>
struct CoroCtx {
    struct promise_type {
        T value;
        CoroCtx get_return_object() {
              return CoroCtx<T>(std::coroutine_handle<promise_type>::from_promise(*this));
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        template<std::convertible_to<T> Return>
        void return_value(Return &&ret) {
            value = std::forward<Return>(ret);
        }
        /*~promise_type() {
            std::cout << "CoroCtx::promise_type destroyed\n";
        }*/
    };

    std::coroutine_handle<promise_type> h;
    CoroCtx(std::coroutine_handle<promise_type> h) : h(h) {}
    ~CoroCtx() { h.destroy(); }
    T operator()() {
        return std::move(h.promise().value);
    }
};

CoroCtx<int> answer(int n) {
    co_return n + 1;
}

int main() {
    auto a = answer(41);
    std::cout << "answer(41) is: " << a() << '\n';
}
