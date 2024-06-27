#include <iostream>
#include "timsort.h"

int main() {
    std::cout << "Timsort application running" << std::endl;

    // Example usage of the Timsort functions
    std::vector<int> arr = {5, 2, 9, 1, 5, 6};
    timsort(arr);

    std::cout << "Sorted array: ";
    for (const auto& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
