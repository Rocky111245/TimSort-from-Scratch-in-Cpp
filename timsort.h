
#ifndef TIMSORT_FROM_SCRATCH_IN_CPP_TIMSORT_H
#define TIMSORT_FROM_SCRATCH_IN_CPP_TIMSORT_H

#include <vector>
#include <stack>
#include <utility>
#include <functional>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <stdexcept>


const int MIN_GALLOP = 7;
typedef std::stack<std::pair<size_t, size_t>> run_stack;

void reverse_range(std::vector<int>& arr, size_t start, size_t end);
size_t count_run(std::vector<int>& arr, size_t minrun, size_t run_start, run_stack& stack);
size_t compute_minrun(size_t n);
int binarySearch(std::vector<int>& arr, int x, int low, int high);
void binary_insertion_sort(std::vector<int>& arr, int key, int location);
void merge_lo(std::vector<int>& arr, size_t start1, size_t len1, size_t start2, size_t len2);
void merge_hi(std::vector<int>& arr, size_t start1, size_t len1, size_t start2, size_t len2);
std::pair<size_t, size_t> merge_at(std::vector<int>& array, std::pair<size_t, size_t> run1, std::pair<size_t, size_t> run2);
void merge_collapse(std::vector<int>& arr, run_stack& stack);
void timsort(std::vector<int>& arr);
std::vector<int> generate_random_data(size_t size);
void benchmark_sort(std::function<void(std::vector<int>&)> sort_function, const std::vector<int>& data, const std::string& name);



#endif //TIMSORT_FROM_SCRATCH_IN_CPP_TIMSORT_H
