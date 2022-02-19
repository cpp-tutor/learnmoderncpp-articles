// BigClass.hpp : minimalist class declaration using pimpl-idiom

#include <vector>
#include <string>
#include <string_view>
#include <memory>

class BigClass {
public:
    BigClass(const std::string& name, const std::vector<int>& data);
    ~BigClass();
    std::string_view getName() const;
    const std::vector<int>& getData() const;
    void setAt(const std::vector<int>::size_type index, const int value);
    BigClass clone() const;
private:
   struct Impl;
    std::shared_ptr<Impl> pImpl;
};
