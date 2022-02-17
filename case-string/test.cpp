#include "case_string.hpp"
#include <iostream>
#include <string>

int main() {
    for (;;) {
        std::cout << "Please enter one of: new, load, save, or quit:\n";
        std::string option;
        std::cin >> option;
        switch(hash_djb2a(option)) {
            case "new"_sh:
                std::cout << "You entered \'new\'\n";
                break;
            case "load"_sh:
                std::cout << "You entered \'load\'\n";
                break;
            case "save"_sh:
                std::cout << "You entered \'save\'\n";
                break;
            case "quit"_sh:
                std::cout << "You entered \'quit\'\n";
                return 0;
            default:
                std::cout << "Command not recognized!\n";
                break;
        }
    }
}
