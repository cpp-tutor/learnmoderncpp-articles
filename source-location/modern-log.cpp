// modern-log.cpp : demonstration of <source_location> header from C++20

#include <source_location>
#include <iostream>
 
void log(std::ostream& os = std::cerr, const std::string_view message = {},
        const std::source_location location =  std::source_location::current())
{
    os << location.file_name() << "("
       << location.line() << ":"
       << location.column() << ") `"
       << location.function_name() << "`: "
       << message << '\n';
}
 
int main() {
    log(std::cout, "Modern \"here1\"");
}
