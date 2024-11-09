#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <iostream>

using namespace std::chrono_literals;

class ThreadID {
    std::thread::id id;
    inline static std::mutex mut;
public:
    ThreadID(const std::thread::id id) : id{ id } {
        std::lock_guard<std::mutex> lock(mut);
        std::cerr << "Launched thread: " << id << '\n';
    }
    ~ThreadID() {
        std::lock_guard<std::mutex> lock(mut);
        std::cerr << "Finished thread: " << id << '\n';
    }
};

void f() {
    ThreadID log(std::this_thread::get_id());
    std::this_thread::sleep_for(3000ms);
}

int main() {
    std::vector<std::thread> threads;
    unsigned threadCount = (std::thread::hardware_concurrency() < 2) ? 1 : std::thread::hardware_concurrency();
    for (int t = 0; t != threadCount; ++t) {
        threads.emplace_back(f);
    }
    for (auto& t : threads) {
        t.join();
    }
}