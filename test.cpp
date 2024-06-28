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

