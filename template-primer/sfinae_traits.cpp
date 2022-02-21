// sfinae_traits.cpp : create a simple but general traits template utilizing SFINAE

#include <type_traits>
#include <vector>
#include <map>

using namespace std;

template<typename...>
using VoidT = void;

template<typename, typename = VoidT<>>
struct HasValueTypeT : false_type {
};

template<typename T>
struct HasValueTypeT<T, VoidT<typename T::value_type>> : true_type {
};

static_assert(HasValueTypeT<vector<int>>::value);
static_assert(HasValueTypeT<map<int,double>>::value);
static_assert(HasValueTypeT<bool>::value); // this line fails to compile
static_assert(HasValueTypeT<void>::value); // and so does this line