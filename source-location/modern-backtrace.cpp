// modern-backtrace.cpp : demonstration exception class using C++20's <source_location>
//                        and C++23's <stacktrace> headers 
// Note: compile with: g++ -std=c++23 modern-backtrace.cpp -lstdc++_libbacktrace
// Note: tested on Compiler Explorer

#include <source_location>
#include <stacktrace>
#include <exception>
#include <string_view>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
 
class LocatedException : public std::exception {
    char *msg = nullptr;
public:
    LocatedException(bool stacktrace = false, 
                std::string_view m = {},
                const std::source_location loc = std::source_location::current(),
                const std::stacktrace trc = std::stacktrace::current()) {
        std::ostringstream oss;
        oss << loc.file_name() << '(' << loc.line() << ':' << loc.column() << ')';
        oss << " in function `" << loc.function_name() << "` " << m << '\n';
        if (stacktrace) {
            oss << "Stacktrace follows:\n" << trc;
        }
        msg = new char[oss.str().size() + 1];
        strcpy(msg, oss.str().c_str());
    }
    LocatedException() = delete;
    LocatedException(const LocatedException&) = delete;
    LocatedException(LocatedException&&) = delete;
    const LocatedException& operator=(const LocatedException&) = delete;
    const LocatedException& operator=(LocatedException&&) = delete;    
    virtual const char *what() const noexcept override {
        return msg;
    }
    virtual ~LocatedException() {
        delete[] msg;
    }
};
 
void h() {
    throw LocatedException(true, "Whoops, shouldn't be here!");
}
 
void g() {
    h();
}
 
void f() {
    g();
}
 
int main() {
    try {
        f();
    }
    catch (std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
