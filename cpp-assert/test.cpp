#include "cpp_assert.hpp"
#include <fstream>

class Error{};

int main() {
    std::cerr << "entering main()\n";
    std::ifstream in{"myfile.txt"};
    log_assert(in, "cannot access myfile.txt");
    cpp_assert(in, Error{});
    std::cerr << "exiting main() normally\n";
    return 0;
}
