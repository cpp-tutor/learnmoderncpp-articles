// triples.cpp : calculate all non-multiple Pythagorean Triples up to set hypotenuse length (default 2500)
// to compile use: /std:c++latest (Visual Studio 2022)
//                 -std=c++20 (g++)
//                 -std=c++20 -stdlib=libc++ (clang++)

#include <iostream>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <numeric>
#include <chrono>
#if defined(__clang__) && (__clang_major__ < 14) // workaround
#include <experimental/coroutine>

namespace std {
  using namespace experimental;
}
#else
#include <coroutine>
#endif

using namespace std::literals::chrono_literals;
using SideT = unsigned;

struct CoroCtx {
    struct promise_type {
        CoroCtx get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() noexcept {}
    };
};

struct AwaitCtx {
    std::coroutine_handle<> *hp;
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<> h) { *hp = h; }
    constexpr void await_resume() const noexcept {}
};

CoroCtx progress(std::coroutine_handle<> *continuation_out, auto n, auto delay) {
    AwaitCtx a{ continuation_out };
    auto t0{ std::chrono::high_resolution_clock::now() };
    for (;;) {
        co_await a;
        if (auto t1{ std::chrono::high_resolution_clock::now() }; (t1 - t0) >= delay) {
            std::cout << "Found " << n() << " triples...\n";
            t0 = t1;
        }
    }
}

int main(const int argc, const char *argv[]) {
    std::vector<std::tuple<SideT,SideT,SideT>> triples;
    std::coroutine_handle<> running_total;
    progress(&running_total, [&triples]{ return triples.size(); }, 500ms);
    SideT max_hypot = (argc == 2) ? atoi(argv[1]) : 2500;
    for (SideT c = 2; c != max_hypot; ++c) {
        for (SideT b = 2; b != c; ++b) {
            SideT a = 2;
            while ((a != b) && ((a * a + b * b) < (c * c))) {
                ++a;
            }
            if ((a * a + b * b) == (c * c)) {
                if (std::gcd(a, b) == 1) {
                    triples.push_back({ a, b, c });
                    running_total();
                }
            }
        }
    }
    std::cout << "Finished with " << triples.size() << " triples:\n";
    for (const auto& t : triples) {
        std::cout << "( " << std::get<0>(t) << ' ' << std::get<1>(t) << ' ' << std::get<2>(t) << " ) ";
    }
    std::cout << '\n';
}
