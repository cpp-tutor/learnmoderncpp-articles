class C4 {
    long long n;
public:
    C4(long long n = 0) : n{ n } {}
};
 
C4 a, b(-100), c(-1ULL << 63), d(0.5);  // bad: c and d are narrowing conversions
C4 e{ -1ULL << 63 }, f{ 0.5 };  // better: e and f are disallowed

class C5 {
    long long n;
public:
    explicit C5(long long n = 0) : n{ n } {}  // note: explicit constructor
};
 
void f(C5 z) {
    //...
}
 
void g() {
    f(100);  // bad, instead use: f(C5{ 100 });
}
