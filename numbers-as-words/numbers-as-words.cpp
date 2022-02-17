// numbers_as_words.cpp : output any positive integer in American usage English
// Version 1.01 (2020/09/12), MIT License, (c) Richard Spencer 2019

// Optionally compile with BOOST_CPP_INT defined to use arbitrary precision
// instead of long long as the Integer type

// Usage: Filename as single argument to test output from "one" to "one million"
//        Run without arguments to enter interactive mode

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef BOOST_CPP_INT
#include <boost/multiprecision/cpp_int.hpp>
using Integer = boost::multiprecision::cpp_int;
#else
using Integer = unsigned long long int;
#endif

using std::cin;
using std::cout;
using std::ofstream;
using std::string;
using std::vector;

string number_triplet(unsigned n) {
    string s{};
    if (n / 100) {
        s += number_triplet(n / 100) + " hundred" + (n % 100 ? " " : "");
    }
    n %= 100;
    if (n < 20) {
        switch (n) {
            case 1: s += "one"; break;
            case 2: s += "two"; break;
            case 3: s += "three"; break;
            case 4: s += "four"; break;
            case 5: s += "five"; break;
            case 6: s += "six"; break;
            case 7: s += "seven"; break;
            case 8: s += "eight"; break;
            case 9: s += "nine"; break;
            case 10: s += "ten"; break;
            case 11: s += "eleven"; break;
            case 12: s += "twelve"; break;
            case 13: s += "thirteen"; break;
            case 14: s += "fourteen"; break;
            case 15: s += "fifteen"; break;
            case 16: s += "sixteen"; break;
            case 17: s += "seventeen"; break;
            case 18: s += "eighteen"; break;
            case 19: s += "nineteen"; break;
        }
    }
    else {
        switch (n / 10) {
            case 2: s += "twenty"; break;
            case 3: s += "thirty"; break;
            case 4: s += "forty"; break;
            case 5: s += "fifty"; break;
            case 6: s += "sixty"; break;
            case 7: s += "seventy"; break;
            case 8: s += "eighty"; break;
            case 9: s += "ninety"; break;
        }
        if (n % 10) {
            s += '-' + number_triplet(n % 10);
        }
    }
    return s;
}

template<typename Number>
void number_to_words(Number n, string& s, const unsigned triplet = 0) {
    if (Number m = n / 1000; m) {
        number_to_words(m, s, triplet + 1);
    }
    const vector triplets = { "", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion", "octillion", "nonillion", "decillion", "undecillion", "duodecillion", "tredecillion", "quattuordecillion", "quindecillion", "sexdecillion", "octodecillion", "novemdecillion", "vigintillion" };
    if (unsigned t = static_cast<unsigned>(n % 1000); t) {
        s += (s.empty() ? "" : " ") + number_triplet(t) + (triplet ? " " : "") + triplets.at(triplet);
    }
}

int main(const int argc, const char *argv[]) {
    if (argc == 2) {
        ofstream file{argv[1]};
        for (Integer i = 1; i <= 1000000; ++i) {
            string s;
            number_to_words(i, s);
            file << s << '\n';
        }
        return 0;
    }
    Integer i{};
    cout << "Please enter a positive number (zero to quit): ";
    cin >> i;
    while (i) {
        string s;
        number_to_words(i, s);
        cout << s << '\n';
        cout << "Please enter another number: ";
        cin >> i;
    }
}
