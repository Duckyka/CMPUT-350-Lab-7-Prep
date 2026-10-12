#include "pack.h"
#include <iostream>
#include <tuple>

int main() { 
    std::cout << pack_detail::packSize<int, float, char> << "\n";
    std::cout << pack_detail::packSize<int, float, char, double, int, bool> << "\n";
    std::cout << pack_detail::packSize<int> << "\n";
    std::cout << pack_detail::packSize<> << "\n";

    std::tuple<int, float, char> t;

    using xType = typename pack_detail::_packIndexToType<2, int, double, char, float>::type;
    
    static_assert(std::is_same<xType, char>::value, "Incorrect type!");
    std::cout << "Successful type received!\n";

    static_assert(std::is_same<pack_detail::_packIndexToType<2, int, double, char, float>::type, char>::value, "Incorrect type!");
    std::cout << "Successful type received!\n";

    static_assert(std::is_same<pack_detail::packIndexToType<2, int, double, char, float>, char>::value, "Incorrect type!");
    std::cout << "Successful type received!\n";

    constexpr int TestIndex = pack_detail::packTypeToIndex<float, int, double, char, float>;
    std::cout << "TestIndex: " << TestIndex << "\n";

    constexpr int TestIndex1 = pack_detail::packTypeToIndex<double, int, double, char, float>;
    std::cout << "TestIndex: " << TestIndex1 << "\n";

    constexpr int TestIndex2 = pack_detail::packTypeToIndex<float, int, float, char, float>;
    std::cout << "TestIndex: " << TestIndex2 << "\n";


    using MyPack = Pack<int, char, double, float>;
    constexpr int testInt = MyPack::size;
    std::cout << "MyPack Size: " << testInt << "\n";
    
    using YType = MyPack::type<2>;
    std::cout << "MyPack TestType: " << std::is_same_v<YType, double> << "\n";

    constexpr int TestIndex10 = MyPack::index<float>;
    std::cout << "MyPack Index: " << TestIndex10 << "\n";

    return 0;
}
