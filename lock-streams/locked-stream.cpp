#include <mutex>
#include <future>
#include <ios>
#include <vector>
#include <iostream>

using namespace std;

mutex ostream_mutex{};

ios_base& lock(ios_base& strm) {
    ostream_mutex.lock();
    return strm;
}

ios_base& unlock(ios_base& strm) {
    ostream_mutex.unlock();
    return strm;
}

void print(int n) {  // note: using lock and unlock
    cout << lock << "This is line " << n << '\n' << unlock;
}

int main() {
    cout << nounitbuf;  // note: turn off buffering
    vector<future<void>> tasks;
    for (int i{}; i != 10; ++i) {
        tasks.push_back(async(launch::async, &print, i + 1));
    }
}
