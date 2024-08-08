#include <gtest/gtest.h>
#include "timsort.h"

// Test suite for Timsort algorithm
class TimsortTest : public ::testing::Test {
protected:
    std::random_device rd;
    std::mt19937 gen{rd()};

    // Function to generate a random vector of integers
    std::vector<int> generateRandomVector(size_t size, int min_val, int max_val) {
        std::vector<int> vec(size);
        std::uniform_int_distribution<> dis(min_val, max_val);
        std::generate(vec.begin(), vec.end(), [&]() { return dis(gen); });
        return vec;
    }

    // Function to check if a vector is sorted
    void checkSorted(const std::vector<int>& vec) {
        EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
    }
};

// Test sorting of random data of various sizes
TEST_F(TimsortTest, SortsRandomData) {
    for (size_t size : {10, 100, 1000, 10000, 100000}) {
        auto vec = generateRandomVector(size, -1000000, 1000000);
        auto vec_copy = vec;
        timsort(vec);
        std::sort(vec_copy.begin(), vec_copy.end());
        EXPECT_EQ(vec, vec_copy);
        checkSorted(vec);
    }
}

// Test sorting of already sorted data
TEST_F(TimsortTest, SortsSortedData) {
    std::vector<int> vec(10000);
    std::iota(vec.begin(), vec.end(), 0);
    auto vec_copy = vec;
    timsort(vec);
    EXPECT_EQ(vec, vec_copy);
    checkSorted(vec);
}

// Test sorting of reverse sorted data
TEST_F(TimsortTest, SortsReverseSortedData) {
    std::vector<int> vec(10000);
    std::iota(vec.rbegin(), vec.rend(), 0);
    timsort(vec);
    checkSorted(vec);
}

// Test sorting of data with many duplicates
TEST_F(TimsortTest, SortsManyDuplicates) {
    std::vector<int> vec(10000, 42);
    timsort(vec);
    checkSorted(vec);
    EXPECT_TRUE(std::all_of(vec.begin(), vec.end(), [](int x) { return x == 42; }));
}

// Test sorting of data with few unique values
TEST_F(TimsortTest, SortsFewUniqueValues) {
    auto vec = generateRandomVector(10000, 1, 10);
    timsort(vec);
    checkSorted(vec);
}

// Test sorting of an empty vector
TEST_F(TimsortTest, SortsEmptyVector) {
    std::vector<int> vec;
    timsort(vec);
    EXPECT_TRUE(vec.empty());
}

// Test sorting of a vector with a single element
TEST_F(TimsortTest, SortsOneElement) {
    std::vector<int> vec = {42};
    timsort(vec);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 42);
}

// Test sorting of a vector with two elements
TEST_F(TimsortTest, SortsTwoElements) {
    std::vector<int> vec = {42, 17};
    timsort(vec);
    checkSorted(vec);
    EXPECT_EQ(vec.size(), 2);
}

// Test sorting of a vector with extreme values
TEST_F(TimsortTest, SortsExtremeValues) {
    std::vector<int> vec = {
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max(),
            0, -1, 1,
            std::numeric_limits<int>::min() + 1,
            std::numeric_limits<int>::max() - 1
    };
    timsort(vec);
    checkSorted(vec);
}

// Test sorting of a vector with alternating values
TEST_F(TimsortTest, SortsAlternatingValues) {
    std::vector<int> vec(1000);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = (i % 2 == 0) ? 0 : 1;
    }
    timsort(vec);
    checkSorted(vec);
}

// Test sorting of a vector with a pipe organ pattern
TEST_F(TimsortTest, SortsPipeOrganValues) {
    std::vector<int> vec(1000);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = (i % 2 == 0) ? i / 2 : 999 - (i / 2);
    }
    timsort(vec);
    checkSorted(vec);
}

// Test sorting of a vector with a repeating pattern
TEST_F(TimsortTest, SortsRepeatingPattern) {
    std::vector<int> pattern = {1, 5, 3, 2, 4};
    std::vector<int> vec;
    for (int i = 0; i < 2000; ++i) {
        vec.push_back(pattern[i % pattern.size()]);
    }
    timsort(vec);
    checkSorted(vec);
}


// Test sorting of a very large input
TEST_F(TimsortTest, HandlesLargeInput) {
    auto vec = generateRandomVector(1000000, -1000000000, 1000000000);
    timsort(vec);
    checkSorted(vec);
}

// Test sorting while preserving duplicates
TEST_F(TimsortTest, PreservesDuplicates) {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    auto vec_copy = vec;
    timsort(vec);
    std::sort(vec_copy.begin(), vec_copy.end());
    EXPECT_EQ(vec, vec_copy);
}

// Test sorting of a vector with all equal elements
TEST_F(TimsortTest, HandlesAllEqualElements) {
    std::vector<int> vec(10000, 42);
    timsort(vec);
    EXPECT_TRUE(std::all_of(vec.begin(), vec.end(), [](int x) { return x == 42; }));
}

// Stress test with multiple large inputs
TEST_F(TimsortTest, StressTest) {
    for (int i = 0; i < 10; ++i) {
        auto vec = generateRandomVector(100000, -1000000, 1000000);
        auto vec_copy = vec;
        timsort(vec);
        std::sort(vec_copy.begin(), vec_copy.end());
        EXPECT_EQ(vec, vec_copy);
    }
}


