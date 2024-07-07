#include "timsort.h"
#include <stdexcept> // For std::out_of_range


// Function to reverse a range in the vector inplace
void reverse_range(std::vector<int>& arr, size_t start, size_t end) {
    while (start < end) {
        std::swap(arr[start++], arr[end--]);
    }
}





// Improved count_run function
size_t count_run(std::vector<int>& arr, size_t minrun, size_t &run_start, run_stack& stack) {
    size_t array_size = arr.size();

    if (run_start >= array_size - 1) return array_size - run_start; // If at the end, return the remaining length

    size_t run_end = run_start + 1;
    bool descending = false;

    // Determine if the run is ascending or descending
    if (arr[run_end] < arr[run_start]) {
        descending = true;
        while (run_end < array_size && arr[run_end] < arr[run_end - 1]) {
            ++run_end;
        }
        // Reverse the descending run to make it ascending
        reverse_range(arr, run_start, run_end - 1);
    } else {
        while (run_end < array_size && arr[run_end] >= arr[run_end - 1]) {
            ++run_end;
        }
    }

    // Extend the run to minrun length if it's too short
    if (run_end - run_start < minrun) {
        run_end = std::min(array_size, run_start + minrun);
        binary_insertion_sort(arr, run_start, run_end - 1);
    }

    size_t length = run_end - run_start;

    // Save the run information in the stack
    stack.push({run_start, length});

    return length;
}








size_t compute_minrun(size_t n) {
    size_t r = 0; // Becomes 1 if any 1 bits are shifted off
    while (n >= 64) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}





//Function to merge two runs and return the new merged run
std::pair<size_t, size_t> merge_at(std::vector<int>&array, std::pair<size_t, size_t> run1, std::pair<size_t, size_t> run2) {
    // Assuming merge_lo and merge_hi functions are implemented and used here
    int start1 = run1.first;
    int len1 = run1.second;
    int start2 = run2.first;
    int len2 = run2.second;

    if (len1 <= len2) {
        merge_lo(array, start1, len1, start2, len2);
    }
    else {
        merge_hi(array, start1, len1, start2, len2);
    }

    return {start1, len1 + len2}; // Returning the new merged run
}





void merge_lo(std::vector<int>& arr, int start1, int len1, int start2, int len2) {
    if (start1 + len1 > arr.size() || start2 + len2 > arr.size()) {
        throw std::out_of_range("merge_lo: Index out of bounds");
    }
    if (len1 == 0 || len2 == 0) return;

    std::vector<int> temp(arr.begin() + start1, arr.begin() + start1 + len1);
    int i = 0, j = start2, k = start1;

    while (i < len1 && j < start2 + len2) {
        if (temp[i] <= arr[j]) {
            arr[k++] = temp[i++];
        } else {
            arr[k++] = arr[j++];
        }
    }
    std::copy(temp.begin() + i, temp.end(), arr.begin() + k);
}

void merge_hi(std::vector<int>& arr, int start1, int len1, int start2, int len2) {
    if (start1 + len1 > arr.size() || start2 + len2 > arr.size()) {
        throw std::out_of_range("merge_hi: Index out of bounds");
    }
    if (len1 == 0 || len2 == 0) return;

    std::vector<int> temp(arr.begin() + start2, arr.begin() + start2 + len2);
    int i = len1 - 1, j = len2 - 1, k = start2 + len2 - 1;

    while (i >= 0 && j >= 0) {
        if (arr[start1 + i] > temp[j]) {
            arr[k--] = arr[start1 + i--];
        } else {
            arr[k--] = temp[j--];
        }
    }
    std::copy_backward(temp.begin(), temp.begin() + j + 1, arr.begin() + k + 1);
}


void merge_collapse(std::vector<int>& arr, run_stack& stack) {
    // Ensure the stack has at least 2 runs to merge

    // top -> C
    // middle -> B
    // bottom -> A

    while (stack.size() > 1) {
        auto top = stack.top(); // C
        stack.pop();
        auto middle = stack.top(); // B
        stack.pop();

        // If the stack still has more elements, we need to check the third most recent run
        if (!stack.empty()) {
            auto bottom = stack.top(); // A
            stack.push(middle);
            stack.push(top);

            // Check if the third run's length is less than or equal to the sum of the two most recent runs
            if (bottom.second <= middle.second + top.second) {
                // Check if the run length combination violates the second invariant
                if (top.second + middle.second <= bottom.second) {
                    stack.pop();
                    stack.pop();
                    auto new_run = merge_at(arr, middle, top); // Merge middle (B) and top (C)
                    stack.push(new_run);
                } else {
                    stack.pop();
                    stack.pop();
                    stack.pop();
                    auto new_run = merge_at(arr, bottom, middle); // Merge bottom (A) and middle (B)
                    stack.push(new_run);
                    stack.push(top); // Push top (C) back on the stack
                }
            } else {
                // No merging needed; restore the stack
                stack.push(middle);
                stack.push(top);
                break;
            }
        } else {

            // Remove both stacks and merge
            auto new_run = merge_at(arr, middle, top);
            stack.push(new_run);


        }
    }
}



// An iterative binary search function to find the position to insert x
int binarySearch(std::vector<int>& arr,int x,int low, int high) {

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // If x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x is greater, ignore left half
        if (arr[mid] < x)
            low = mid + 1;
            // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // Return the position where x should be inserted
    return low;
}

// Binary insertion sort function
void binary_insertion_sort(std::vector<int>& arr, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; ++i) {
        int key = arr[i];
        size_t j = i - 1;
        size_t loc = binarySearch(arr, key, left, j);

        while (j >= loc) {
            arr[j + 1] = arr[j];
            if (j == left) break;
            --j;
        }
        arr[loc] = key;
    }
}





// Timsort implementation
void timsort(std::vector<int>& arr) {
    size_t minrun = compute_minrun(arr.size());
    run_stack stack;
    size_t run_start = 0;

    // Identify and push runs onto the stack
    while (run_start < arr.size()) {
        size_t run_length = count_run(arr, minrun, run_start, stack);
        run_start += run_length;
    }

    // Merge runs on the stack
    merge_collapse(arr, stack);
}

// Function to generate a random dataset
std::vector<int> generate_random_data(size_t size) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    for (size_t i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
    return data;
}

// Function to benchmark a sorting function
void benchmark_sort(std::function<void(std::vector<int>&)> sort_function, const std::vector<int>& data, const std::string& name) {
    std::vector<int> copy = data;

    auto start = std::chrono::high_resolution_clock::now();
    sort_function(copy);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << name << " took " << duration.count() << " seconds." << std::endl;
}

