#include <future>
#include <thread>
#include <vector>
#include <iostream>

void f(std::promise<long long>& p, int begin, int end) {
    long long sum{};
    for (int value = begin; value != end; ++value) {
        sum += value + 1;
    }
    p.set_value(sum);
}

int main() {
    const int sumSize = 1'000'000'000;
    unsigned threadCount = (std::thread::hardware_concurrency() < 2) ? 1 : std::thread::hardware_concurrency();
    std::vector<std::promise<long long>> promises(threadCount);
    std::vector<std::future<long long>> futures(threadCount);
    std::vector<std::thread> threads;

    int portionBegin{}, portionEnd{};
    for (int t = 0; t != threadCount; ++t) {
        portionEnd = portionBegin + sumSize / threadCount;
        threads.emplace_back(f, std::ref(promises.at(t)), portionBegin, portionEnd);
        portionBegin = portionEnd;
        futures.at(t) = promises.at(t).get_future();
    }
    
    for (auto& t : threads) {
        t.join();
    }
    long long sum{};
    for (auto& f : futures) {
        sum += f.get();
    }
    std::cout << "Sum of first " << sumSize << " numbers is: " << sum << '\n';
}