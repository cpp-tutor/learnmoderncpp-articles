// iterator2.cpp : list a directory using a filesystem::directory_iterator

#include <string>
#include <iostream>
#include <filesystem>
 
int main(const int argc, const char *argv[])
{
    if (argc != 2) {
        std::cerr << "Syntax: " << argv[0] << " directory-to-list\n";
        return 1;
    }
    std::string path = argv[1];
    std::cout << "Listing for directory: " << path << '\n';
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::cout << '\t' << entry.path() << std::endl;
    }
}
