#include <thread>

void f() {
    for (;;) {}
}

int main() {
    std::thread t(f);
}