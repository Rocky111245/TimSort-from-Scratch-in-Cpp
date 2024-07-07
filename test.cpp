#include <gtest/gtest.h>
#include "timsort.h"

// Test suite for merge_lo
class MergeLoTest : public ::testing::Test {
protected:
    void SetUp() override {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();
        std::cout << "Start of test -> " << test_info->test_case_name() << "." << test_info->name() << std::endl;
    }

    void TearDown() override {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();
        std::cout << "End of test -> " << test_info->test_case_name() << "." << test_info->name() << std::endl;
        std::cout << std::endl; // Add a gap between tests
    }
};

TEST_F(MergeLoTest, BasicMerge) {
    std::vector<int> arr = {1, 3, 5, 2, 4, 6};
    std::cout << "Initial array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    merge_lo(arr, 0, 3, 3, 3);

    std::cout << "\033[33m"; // Set color to yellow
    std::cout << "Array after merge_lo: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << "\033[0m";  // Reset color

    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST_F(MergeLoTest, UnequalSizes) {
    std::vector<int> arr = {1, 4, 7, 2, 3, 6, 8};
    std::cout << "Initial array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    merge_lo(arr, 0, 3, 3, 4);

    std::cout << "\033[33m"; // Set color to yellow
    std::cout << "Array after merge_lo: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << "\033[0m";  // Reset color

    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 6, 7, 8}));
}

TEST_F(MergeLoTest, SingleElement) {
    std::vector<int> arr = {5, 1};
    std::cout << "Initial array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    merge_lo(arr, 0, 1, 1, 1);

    std::cout << "\033[33m"; // Set color to yellow
    std::cout << "Array after merge_lo: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << "\033[0m";  // Reset color

    EXPECT_EQ(arr, (std::vector<int>{1, 5}));
}

TEST_F(MergeLoTest, AllElementsInOneSubarray) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    std::cout << "Initial array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    merge_lo(arr, 0, 3, 3, 3);

    std::cout << "\033[33m"; // Set color to yellow
    std::cout << "Array after merge_lo: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << "\033[0m";  // Reset color

    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST_F(MergeLoTest, AlreadyMerged) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    std::cout << "Initial array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    merge_lo(arr, 0, 3, 3, 3);

    std::cout << "\033[33m"; // Set color to yellow
    std::cout << "Array after merge_lo: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << "\033[0m";  // Reset color

    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST_F(MergeLoTest, EmptySubarrays) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    std::cout << "Initial array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    merge_lo(arr, 0, 0, 3, 3);

    std::cout << "\033[33m"; // Set color to yellow
    std::cout << "Array after merge_lo: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << "\033[0m";  // Reset color

    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST_F(MergeLoTest, OutOfBounds) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    EXPECT_THROW(merge_lo(arr, 0, 4, 3, 3), std::out_of_range);
}



class TimsortTest : public ::testing::Test {
protected:
    std::random_device rd;
    std::mt19937 gen{rd()};

    std::vector<int> generateRandomVector(size_t size, int min_val, int max_val) {
        std::vector<int> vec(size);
        std::uniform_int_distribution<> dis(min_val, max_val);
        std::generate(vec.begin(), vec.end(), [&]() { return dis(gen); });
        return vec;
    }

    void checkSorted(const std::vector<int>& vec) {
        EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
    }
};

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

TEST_F(TimsortTest, SortsSortedData) {
    std::vector<int> vec(10000);
    std::iota(vec.begin(), vec.end(), 0);
    auto vec_copy = vec;
    timsort(vec);
    EXPECT_EQ(vec, vec_copy);
    checkSorted(vec);
}

TEST_F(TimsortTest, SortsReverseSortedData) {
    std::vector<int> vec(10000);
    std::iota(vec.rbegin(), vec.rend(), 0);
    timsort(vec);
    checkSorted(vec);
}

TEST_F(TimsortTest, SortsManyDuplicates) {
    std::vector<int> vec(10000, 42);
    timsort(vec);
    checkSorted(vec);
    EXPECT_TRUE(std::all_of(vec.begin(), vec.end(), [](int x) { return x == 42; }));
}

TEST_F(TimsortTest, SortsFewUniqueValues) {
    auto vec = generateRandomVector(10000, 1, 10);
    timsort(vec);
    checkSorted(vec);
}

TEST_F(TimsortTest, SortsEmptyVector) {
    std::vector<int> vec;
    timsort(vec);
    EXPECT_TRUE(vec.empty());
}

TEST_F(TimsortTest, SortsOneElement) {
    std::vector<int> vec = {42};
    timsort(vec);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 42);
}

TEST_F(TimsortTest, SortsTwoElements) {
    std::vector<int> vec = {42, 17};
    timsort(vec);
    checkSorted(vec);
    EXPECT_EQ(vec.size(), 2);
}

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

TEST_F(TimsortTest, SortsAlternatingValues) {
    std::vector<int> vec(1000);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = (i % 2 == 0) ? 0 : 1;
    }
    timsort(vec);
    checkSorted(vec);
}

TEST_F(TimsortTest, SortsPipeOrganValues) {
    std::vector<int> vec(1000);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = (i % 2 == 0) ? i / 2 : 999 - (i / 2);
    }
    timsort(vec);
    checkSorted(vec);
}

TEST_F(TimsortTest, SortsRepeatingPattern) {
    std::vector<int> pattern = {1, 5, 3, 2, 4};
    std::vector<int> vec;
    for (int i = 0; i < 2000; ++i) {
        vec.push_back(pattern[i % pattern.size()]);
    }
    timsort(vec);
    checkSorted(vec);
}

TEST_F(TimsortTest, SortsNearlySortedData) {
    std::vector<int> vec(10000);
    std::iota(vec.begin(), vec.end(), 0);
    for (int i = 0; i < 100; ++i) {
        int idx1 = gen() % vec.size();
        int idx2 = gen() % vec.size();
        std::swap(vec[idx1], vec[idx2]);
    }

    auto print_partial = [](const std::vector<int>& v) {
        std::cout << "First 20: ";
        for (int i = 0; i < 20 && i < v.size(); ++i) std::cout << v[i] << " ";
        std::cout << "\nLast 20: ";
        for (int i = std::max(0, static_cast<int>(v.size()) - 20); i < v.size(); ++i) std::cout << v[i] << " ";
        std::cout << std::endl;
    };

    std::cout << "Before sorting:\n";
    print_partial(vec);

    auto vec_copy = vec;
    timsort(vec);
    std::sort(vec_copy.begin(), vec_copy.end());

    std::cout << "After sorting:\n";
    print_partial(vec);

    // Count inversions
    int inversions = 0;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        if (vec[i] > vec[i+1]) ++inversions;
    }
    std::cout << "Number of inversions: " << inversions << std::endl;

    // Compare with std::sort
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] != vec_copy[i]) {
            std::cout << "Mismatch at index " << i << ": timsort=" << vec[i] << ", std::sort=" << vec_copy[i] << std::endl;
            break;
        }
    }

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
    EXPECT_EQ(vec, vec_copy);
}

TEST_F(TimsortTest, HandlesLargeInput) {
    auto vec = generateRandomVector(1000000, -1000000000, 1000000000);
    timsort(vec);
    checkSorted(vec);
}

TEST_F(TimsortTest, PreservesDuplicates) {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    auto vec_copy = vec;
    timsort(vec);
    std::sort(vec_copy.begin(), vec_copy.end());
    EXPECT_EQ(vec, vec_copy);
}

TEST_F(TimsortTest, HandlesAllEqualElements) {
    std::vector<int> vec(10000, 42);
    timsort(vec);
    EXPECT_TRUE(std::all_of(vec.begin(), vec.end(), [](int x) { return x == 42; }));
}

TEST_F(TimsortTest, StressTest) {
    for (int i = 0; i < 10; ++i) {
        auto vec = generateRandomVector(100000, -1000000, 1000000);
        auto vec_copy = vec;
        timsort(vec);
        std::sort(vec_copy.begin(), vec_copy.end());
        EXPECT_EQ(vec, vec_copy);
    }
}


