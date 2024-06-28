#include "timsort.h"
#include <iostream>
#include <stdexcept> // For std::out_of_range

int main() {
    try {
        std::cout << "Timsort application running" << std::endl;

        // Generate a random array of size 1111
        std::vector<int> arr = generate_random_data(1111);

        // Apply Timsort
        timsort(arr);

        // Check if the array is sorted and print the array
        bool is_sorted = true;
        int unsorted_index = -1;
        std::cout << "Sorted array: ";
        for (int i = 0; i < arr.size(); ++i) {
            std::cout << arr[i] << " ";
            if (i > 0 && arr[i-1] > arr[i]) {
                is_sorted = false;
                if (unsorted_index == -1) {
                    unsorted_index = i;
                }
            }
        }
        std::cout << std::endl;

        if (is_sorted) {
            std::cout << "Array sorted" << std::endl;
        } else {
            std::cout << "Array not sorted" << std::endl;
            std::cout << "Array started to be unsorted at index " << unsorted_index << std::endl;
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
