#include <iostream>
#include <array>

using namespace std;

int main() {
    double x;
    auto y = [&x]{ return x / 2 + 5; };
    auto y2 = [&x]{ return x * x / 100; };

    constexpr int sizeX = 79, sizeY = 24, originX = 39, originY = 12;
    constexpr int minX = -39, maxX = 39, minY = -12, maxY = 11;
    array<array<char,sizeX>,sizeY> graph;
    for (auto& y : graph) {
        for (auto& x : y) {
            x = ' ';
        }
    }

    auto plot = [&](auto f) {
        for (x = minX; x <= maxX; ++x) {
             auto y = f();
             if (y >= minY && y <= maxY) {
                 graph[sizeY - 1 - (y + originY)][x + originX] = '#';
             }
        }
    };

    plot(y);
    plot(y2);

    for (auto& y : graph) {
        for (auto& x : y) {
            cout << x;
        }
        cout << '\n';
    }

}