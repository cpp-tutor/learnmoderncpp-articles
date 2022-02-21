#include <future>
#include <vector>
#include <iostream>

using namespace std;

void print(int n) {
    cout << "This is line " << n << '\n';
}

int main() {
    vector<future<void>> tasks;
    for (int i{}; i != 10; ++i) {
        tasks.push_back(async(launch::async, &print, i + 1));
    }
}
