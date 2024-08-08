#include "timsort.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>






int main() {
    run_sort(20);
    run_sort(65);
    run_sort(1000);
    run_sort(10000);  // Add more sizes as needed
    run_sort(211111); // Original large size

    return 0;
}
