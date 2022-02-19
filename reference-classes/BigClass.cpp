#include "BigClass.hpp"

struct BigClass::Impl {
    std::string name;
    std::vector<int> data;
};

BigClass::BigClass(const std::string& name, const std::vector<int>& data)
    : pImpl{ std::make_shared<Impl>(Impl{ name, data }) }
    {}

BigClass::~BigClass() {}

std::string_view BigClass::getName() const
    { return pImpl->name;
}

const std::vector<int>& BigClass::getData() const {
    return pImpl->data;
}

void BigClass::setAt(const std::vector<int>::size_type index, const int value) {
    if (index < pImpl->data.size()) {
        pImpl->data[index] = value;
    }
}

BigClass BigClass::clone() const {
    return BigClass(pImpl->name, pImpl->data);
}
