#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cassert>
#include <limits>
#include "timsort.h"

// Function to check if a vector is sorted
bool is_sorted(const std::vector<int>& arr) {
    return std::is_sorted(arr.begin(), arr.end());
}

// Function to generate a random vector
std::vector<int> generate_random_vector(size_t size, int min_val, int max_val) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min_val, max_val);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }
    return vec;
}

// Test case 1: Sort random data
void test_random_data() {
    std::vector<int> sizes = {100, 1000, 10000, 100000};
    for (size_t size : sizes) {
        std::vector<int> data = generate_random_vector(size, -1000000, 1000000);
        std::vector<int> data_copy = data;

        timsort(data);
        std::sort(data_copy.begin(), data_copy.end());

        assert(data == data_copy);
        assert(is_sorted(data));
        std::cout << "Random data test passed for size " << size << std::endl;
    }
}

// Test case 2: Sort already sorted data
void test_sorted_data() {
    std::vector<int> data(10000);
    std::iota(data.begin(), data.end(), 0);  // Fill with 0, 1, 2, ..., 9999

    std::vector<int> data_copy = data;
    timsort(data);

    assert(data == data_copy);
    assert(is_sorted(data));
    std::cout << "Sorted data test passed" << std::endl;
}

// Test case 3: Sort reverse sorted data
void test_reverse_sorted_data() {
    std::vector<int> data(10000);
    std::iota(data.rbegin(), data.rend(), 0);  // Fill with 9999, 9998, ..., 0

    timsort(data);

    assert(is_sorted(data));
    std::cout << "Reverse sorted data test passed" << std::endl;
}

// Test case 4: Sort data with many duplicates
void test_many_duplicates() {
    std::vector<int> data(10000, 42);  // 10000 elements, all 42

    timsort(data);

    assert(is_sorted(data));
    assert(std::all_of(data.begin(), data.end(), [](int x) { return x == 42; }));
    std::cout << "Many duplicates test passed" << std::endl;
}

// Test case 5: Sort data with few unique values
void test_few_unique_values() {
    std::vector<int> data = generate_random_vector(10000, 1, 10);

    timsort(data);

    assert(is_sorted(data));
    std::cout << "Few unique values test passed" << std::endl;
}

// Test case 6: Sort empty vector
void test_empty_vector() {
    std::vector<int> data;

    timsort(data);

    assert(data.empty());
    std::cout << "Empty vector test passed" << std::endl;
}

// Test case 7: Sort vector with one element
void test_one_element() {
    std::vector<int> data = {42};

    timsort(data);

    assert(data.size() == 1);
    assert(data[0] == 42);
    std::cout << "One element test passed" << std::endl;
}

// Test case 8: Sort vector with two elements
void test_two_elements() {
    std::vector<int> data = {42, 17};

    timsort(data);

    assert(data.size() == 2);
    assert(is_sorted(data));
    std::cout << "Two elements test passed" << std::endl;
}

// Test case 9: Sort data with extreme values
void test_extreme_values() {
    std::vector<int> data = {
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max(),
            0,
            -1,
            1,
            std::numeric_limits<int>::min() + 1,
            std::numeric_limits<int>::max() - 1
    };

    timsort(data);

    assert(is_sorted(data));
    std::cout << "Extreme values test passed" << std::endl;
}

// Main function to run all tests
int main() {
    try {
        test_random_data();
        test_sorted_data();
        test_reverse_sorted_data();
        test_many_duplicates();
        test_few_unique_values();
        test_empty_vector();
        test_one_element();
        test_two_elements();
        test_extreme_values();

        std::cout << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}