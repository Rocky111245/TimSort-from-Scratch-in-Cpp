#include <vector>
#include <algorithm> // For std::sort
#include <iostream>
#include <stack>
#include <chrono> // For time measurement
#include <random> // For generating test datasets
#include <functional> // For std::function


const int MIN_GALLOP = 7;

typedef std::stack<std::pair<size_t, size_t>> run_stack;

void reverse_range(std::vector<int>& arr, size_t start, size_t end);
size_t count_run(std::vector<int>& arr, size_t minrun, size_t run_start, run_stack& stack);
size_t compute_minrun(size_t n);
int binarySearch(std::vector<int>& arr,int x,int low, int high);
void binary_insertion_sort(std::vector<int>& arr, int key,int location);
void merge_lo(std::vector<int>& arr, size_t start1, size_t len1, size_t start2, size_t len2);
void merge_hi(std::vector<int>& arr, size_t start1, size_t len1, size_t start2, size_t len2);
std::pair<size_t, size_t> merge_at(std::vector<int>&array, std::pair<size_t, size_t> run1, std::pair<size_t, size_t> run2);
void merge_collapse(std::vector<int>& arr, run_stack& stack);
std::vector<int> generate_random_data(size_t size);
void benchmark_sort(std::function<void(std::vector<int>&)> sort_function, const std::vector<int>& data, const std::string& name);
void timsort(std::vector<int>& arr);


int main() {
    std::vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};

    std::cout << "Original array: ";
    for (const int &val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    timsort(arr);

    std::cout << "Sorted array: ";
    for (const int &val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}







// Function to reverse a range in the vector inplace
void reverse_range(std::vector<int>& arr, size_t start, size_t end) {
    while (start < end) {
        std::swap(arr[start++], arr[end--]);
    }
}




//Function to count the length of the next run in the array and save run information
size_t count_run(std::vector<int>& arr, size_t minrun, size_t run_start, run_stack& stack) {
    size_t array_size = arr.size();

    if (run_start >= array_size - 1) return array_size - run_start; // If at the end, return the remaining length

    size_t run_end = run_start + 1;

    // Check if the run is ascending
    if (arr[run_end] >= arr[run_start]) {
        while (run_end < array_size && arr[run_end] >= arr[run_end - 1]) {
            ++run_end;
        }

        // Extend the run to the minrun length if it's too short
        if (run_end - run_start < minrun) {
            std::vector<int> temp_array(arr.begin() + run_start, arr.begin() + run_end);

            while (temp_array.size() < minrun && run_end < array_size) {
                int location = binarySearch(temp_array, arr[run_end], 0, temp_array.size() - 1);
                temp_array.insert(temp_array.begin() + location, arr[run_end]);
                ++run_end;
            }

            std::copy(temp_array.begin(), temp_array.end(), arr.begin() + run_start);
        }
    } else { // The run is descending
        while (run_end < array_size && arr[run_end] < arr[run_end - 1]) {
            ++run_end;
        }

        // Reverse the descending run to make it ascending
        reverse_range(arr, run_start, run_end - 1);

        // Extend the run to the minrun length if it's too short
        if (run_end - run_start < minrun) {
            std::vector<int> temp_array(arr.begin() + run_start, arr.begin() + run_end);

            while (temp_array.size() < minrun && run_end < array_size) {
                int location = binarySearch(temp_array, arr[run_end], 0, temp_array.size() - 1);
                temp_array.insert(temp_array.begin() + location, arr[run_end]);
                ++run_end;
            }

            std::copy(temp_array.begin(), temp_array.end(), arr.begin() + run_start);
        }
    }

    size_t length = run_end - run_start;

    // Save the run information in the stack
    stack.push({run_start, length});

    return length;
}






//this is not a readable function and a more readable function shall be introduced
// Function to compute minrun based on the size of the array
size_t compute_minrun(size_t n) {
    size_t r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1; // divides the size by 2
    }
    return n + r;
}




//Function to merge two runs and return the new merged run
std::pair<size_t, size_t> merge_at(std::vector<int>&array, std::pair<size_t, size_t> run1, std::pair<size_t, size_t> run2) {
    // Assuming merge_lo and merge_hi functions are implemented and used here
    size_t start1 = run1.first;
    size_t len1 = run1.second;
    size_t start2 = run2.first;
    size_t len2 = run2.second;

    if (len1 <= len2) {
        merge_lo(array, start1, len1, start2, len2);
    } else {
        merge_hi(array, start1, len1, start2, len2);
    }

    return {start1, len1 + len2}; // Returning the new merged run
}

void merge_lo(std::vector<int>& arr, size_t start1, size_t len1, size_t start2, size_t len2) {
    std::vector<int> temp(arr.begin() + start1, arr.begin() + start1 + len1);
    size_t i = 0; // Index for temp
    size_t j = start2; // Index for arr[start2]
    size_t k = start1; // Index for merged array position

    while (i < len1 && j < start2 + len2) {
        if (temp[i] <= arr[j]) {
            arr[k++] = temp[i++];
        } else {
            arr[k++] = arr[j++];
        }
    }
    while (i < len1) {
        arr[k++] = temp[i++];
    }
}

void merge_hi(std::vector<int>& arr, size_t start1, size_t len1, size_t start2, size_t len2) {
    std::vector<int> temp(arr.begin() + start2, arr.begin() + start2 + len2);
    size_t i = start1 + len1 - 1; // Index for arr[start1 + len1 - 1]
    size_t j = len2 - 1; // Index for temp
    size_t k = start2 + len2 - 1; // Index for merged array position

    while (j < len2 && i >= start1) {
        if (arr[i] > temp[j]) {
            arr[k--] = arr[i--];
        } else {
            arr[k--] = temp[j--];
        }
    }
    while (j < len2) {
        arr[k--] = temp[j--];
    }
}





void merge_collapse(std::vector<int>& arr, run_stack& stack) {
    // Ensure the stack has at least 2 runs to merge
    while (stack.size() > 1) {
        auto top1 = stack.top();
        stack.pop();
        auto top2 = stack.top();
        stack.pop();

        // If the stack still has more elements, we need to check the third most recent run
        if (!stack.empty()) {
            auto top3 = stack.top();
            stack.push(top2);
            stack.push(top1);

            // Check if the third run's length is less than or equal to the sum of the two most recent runs
            if (top3.second <= top2.second + top1.second) {
                if (top1.second < top3.second) {
                    // Ensure only top1 is left, the merge_at will return the new merged run size
                    stack.pop();
                    stack.pop();

                    // Merge top2 and top3
                    auto new_run = merge_at(arr,top2, top3); // This should return the new merged run size
                    stack.push(new_run);
                } else {
                    // Remove all 3
                    stack.pop();
                    stack.pop();
                    stack.pop();

                    // Merge top1 and top2
                    auto new_run = merge_at(arr,top1, top2); // Merge top1 and top2
                    stack.push(new_run);
                    stack.push(top3);
                }
            } else {
                // Just put them back, no need for customizations
                stack.push(top2);
                stack.push(top1);
                break;
            }
        } else {
            stack.push(top2);
            stack.push(top1);

            if (top2.second <= top1.second) {
                // Remove both stacks and return new stack size
                stack.pop();
                stack.pop();
                auto new_run = merge_at(arr,top1, top2);
                stack.push(new_run);
            } else {
                break;
            }
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

// Function to perform binary insertion sort
void binary_insertion_sort(std::vector<int>& arr, int key,int location) {
    int size=arr.size();
    arr.resize(size+1);

    for(int i=size;i>location;i--){
        arr[i]=arr[i-1];
    }
    arr[location]=key;

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
    std::uniform_int_distribution<> dis(1, 1000000);

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
