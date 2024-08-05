
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
size_t gallop(const std::vector<int>& arr, int key, size_t current, size_t end_index);
void reverse_range(std::vector<int>& arr, size_t start, size_t end);
size_t count_run(std::vector<int>& arr, size_t minrun, size_t &run_start, run_stack& stack) ;
std::vector<int> generate_random_data(size_t size);
double benchmark_sort(std::function<void(std::vector<int>&)> sort_function, const std::vector<int>& data, const std::string& name, int runs = 10);
size_t compute_minrun(size_t n);
int binarySearch(std::vector<int>& arr, int x, int low, int high);
void binary_insertion_sort(std::vector<int>& arr, size_t left, size_t right) ;
std::pair<size_t, size_t> merge_at(std::vector<int>&array, std::pair<size_t, size_t> run1, std::pair<size_t, size_t> run2);
void merge_lo(std::vector<int>& arr, int start1, int  len1, int  start2, int  len2);
void merge_hi(std::vector<int>& arr, int start1, int len1, int  start2, int len2);
std::pair<size_t, size_t> merge_at(std::vector<int>& array, std::pair<size_t, size_t> run1, std::pair<size_t, size_t> run2);
void merge_collapse(std::vector<int>& arr, run_stack& stack);
void timsort(std::vector<int>& arr);




#endif //TIMSORT_FROM_SCRATCH_IN_CPP_TIMSORT_H