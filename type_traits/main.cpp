#include <iostream>
#include "type_traits.hpp"

int main() {
    // Test is_integral trait
    std::cout << "Testing is_integral:\n";
    std::cout << "is_integral<int>::value: " << TypeTraits::is_integral_v<int> << "\n";
    std::cout << "is_integral<float>::value: " << TypeTraits::is_integral_v<float> << "\n";

    // Test is_same trait
    std::cout << "\nTesting is_same:\n";
    std::cout << "is_same<int, int>::value: " << TypeTraits::is_same_v<int, int> << "\n";
    std::cout << "is_same<int, float>::value: " << TypeTraits::is_same_v<int, float> << "\n";

    // Test remove_const trait
    std::cout << "\nTesting remove_const:\n";
    std::cout << "remove_const<const int>::type is int: " << TypeTraits::is_same_v<TypeTraits::remove_const_t<const int>, int> << "\n";

    // Test is_const trait
    std::cout << "\nTesting is_const:\n";
    std::cout << "is_const<const int>::value: " << TypeTraits::is_const_v<const int> << "\n";
    std::cout << "is_const<int>::value: " << TypeTraits::is_const_v<int> << "\n";

    // Test is_pointer trait
    std::cout << "\nTesting is_pointer:\n";
    std::cout << "is_pointer<int*>::value: " << TypeTraits::is_pointer<int*>::value << "\n";
    std::cout << "is_pointer<int>::value: " << TypeTraits::is_pointer<int>::value << "\n";

    // Test remove_pointer trait
    std::cout << "\nTesting remove_pointer:\n";
    std::cout << "remove_pointer<int*>::type is int: " << TypeTraits::is_same_v<TypeTraits::remove_pointer_t<int*>, int> << "\n";

    // Test is_array trait
    std::cout << "\nTesting is_array:\n";
    std::cout << "is_array<int[]>::value: " << TypeTraits::is_array_v<int[]> << "\n";
    std::cout << "is_array<int[5]>::value: " << TypeTraits::is_array_v<int[5]> << "\n";
    std::cout << "is_array<int>::value: " << TypeTraits::is_array_v<int> << "\n";

    // Test is_reference trait
    std::cout << "\nTesting is_reference:\n";
    std::cout << "is_reference<int&>::value: " << TypeTraits::is_reference_v<int&> << "\n";
    std::cout << "is_reference<int>::value: " << TypeTraits::is_reference_v<int> << "\n";

    std::cout << "\nAll tests completed.\n";
    return 0;
}
