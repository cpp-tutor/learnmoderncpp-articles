class B1 {
    int n{ 42 };
public:
    const int get() const { return n; }
};
 
class D1 : private B1 {
public:
    using B1::get;
};
 
int main() {
    D1 derived;
    auto n = derived.get();
}
