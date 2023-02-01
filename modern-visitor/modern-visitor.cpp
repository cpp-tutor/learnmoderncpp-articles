// modern-visitor.cpp : example visitor-pattern in modern C++

#include <iostream>
#include <variant>
 
template<typename... Base>
struct Visitor : Base... {
    using Base::operator()...;
};
 
template<typename...T> Visitor(T...) -> Visitor<T...>;
 
class Liquor {
    double price;
public:
    Liquor(double price) : price{ price } {}
    operator double() const { return price; }
};
 
class Tobacco {
    double item;
public:
    Tobacco(double itemPrice) : item{ itemPrice } {}
    double getItemPrice() const { return item; }
};
 
class Necessity {
    unsigned costInCents;
public:
    Necessity(double cost) : costInCents{ static_cast<unsigned>(cost * 100) } {}
    operator double() const { return costInCents / 100.0; }
};
 
Visitor TaxVisitor{
    [](const Liquor& liquor){ double l = liquor; return l * 1.5; },
    [](const Tobacco& tobacco) { return tobacco.getItemPrice() * 1.8; },
    [](const Necessity& necessity) { double n = necessity; return n * 1.0; }
};
 
Visitor TaxFreeVisitor{
    [](const Tobacco& tobacco) { return tobacco.getItemPrice() * 1.0; },
    [](const auto& any) { double price = any; return price * 1.0; }
};
 
int main() {
    using Visitable = std::variant<Liquor,Tobacco,Necessity>;
    Liquor whiskey{ 25.99 };
    Tobacco cigs{ 13.49 };
    Necessity bread{ 1.29 };
     
    std::cout.precision(2);
    std::cout << "Many Items Taxable\n" << std::fixed;
    std::cout << "  Whiskey:    $" << std::visit(TaxVisitor, Visitable(whiskey)) << '\n';
    std::cout << "  Cigarettes: $" << std::visit(TaxVisitor, Visitable(cigs)) << '\n';
    std::cout << "  Bread:      $" << std::visit(TaxVisitor, Visitable(bread)) << '\n';
 
    std::cout << "All Items Tax-Free\n";
    std::cout << "  Whiskey:    $" << std::visit(TaxFreeVisitor, Visitable(whiskey)) << '\n';
    std::cout << "  Cigarettes: $" << std::visit(TaxFreeVisitor, Visitable(cigs)) << '\n';
    std::cout << "  Bread:      $" << std::visit(TaxFreeVisitor, Visitable(bread)) << '\n';
}
