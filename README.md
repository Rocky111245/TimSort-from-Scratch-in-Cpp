# TimSort Implementation in C++

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Implementation Details](#implementation-details)
- [Building and Running](#building-and-running)
    - [Prerequisites](#prerequisites)
    - [Building with CMake](#building-with-cmake)
    - [Running with Docker](#running-with-docker)
- [Testing](#testing)
- [Function Overview](#function-overview)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

# TimSort Implementation in C++

## Introduction

This repository contains a faithful enactment of the original TimSort algorithm as described by Tim Peters. TimSort is arguably the most complex sorting algorithm to date, combining the strengths of merge sort and insertion sort to achieve high efficiency, especially on real-world data that often contains ordered subsequences.

The implementation is based on the reference written by Tim Peters himself, which can be found [here](https://bugs.python.org/file4451/timsort.txt). This project aims to provide an educational resource for understanding the intricacies of the TimSort algorithm.

The primary goal of this project is educational. While many sorting algorithms are well-documented and widely understood, TimSort remains somewhat obscure, with few educational resources providing in-depth explanations of its intricacies. This sparked our interest in developing this implementation, aiming to shed light on the inner workings of this fascinating algorithm.

It's important to note that this implementation is intended for educational purposes only. It is not meant to compete with `std::sort` in C++, which has been optimized over years of development. Instead, this project places special emphasis on illustrating how the TimSort architecture works, providing a clear and detailed view of its components and logic.

Key aspects of this implementation:

1. Enactment done using reference written by Tim Peters himself.
2. Implementation was written to be as close to the source material as possible.
3. Code and ideas written entirely in C++, leveraging its performance characteristics and expressive power.
4. Comprehensive documentation explaining what each function of the algorithm does.

This project serves as a bridge between the theoretical understanding of TimSort and its practical implementation, offering insights into the algorithm's design choices and optimizations.
## Features

- ✅ Faithful implementation of the original TimSort algorithm
- 📚 Implementation closely follows the source material
- 🖥️ Written entirely in C++ for performance and clarity
- 🧪 Comprehensive test suite to verify correctness
- 🐳 Docker support for easy setup and execution


## Building and Running

### Prerequisites

- CMake 3.26 or higher
- C++23 compatible compiler
- Docker (optional, for containerized execution)

### Building with CMake

1. Clone the repository:
   ```bash
   git clone https://github.com/Rocky111245/TimSort-from-Scratch-in-Cpp.git
   cd TimSort-from-Scratch-in-Cpp
   ```

2. Create a build directory and run CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

   This will download Google Test, configure the project, and build both the main program and the test suite.

3. Run the main program:
   ```bash
   ./TimSortMain
   ```

   This will execute the main program, which demonstrates the TimSort algorithm on various array sizes.

4. Run the tests:
   ```bash
   ./TestRunner
   ```

   This will run the comprehensive test suite using Google Test to verify the correctness of the TimSort implementation.

Note: This project requires CMake 3.26 or higher and uses C++23 standard. It's configured for Debug mode by default.

### Running with Docker

To run the TimSort implementation using Docker, follow these steps:

1. Clone the repository:
    ```bash
   git clone https://github.com/Rocky111245/TimSort-from-Scratch-in-Cpp.git
   cd TimSort-from-Scratch-in-Cpp
    ```
3. Build the Docker image:
   ```bash
   docker build -t cpp-timsort .
   ```

4. To run the main program, which demonstrates TimSort on various array sizes:
   ```bash
   docker run -it --rm cpp-timsort
   ```

   Note: This uses the default CMD specified in the Dockerfile.

5. To execute the test suite:
   ```bash
   docker run -it --rm cpp-timsort ./build/TestRunner
   ```

6. If you need to run the main program explicitly:
   ```bash
   docker run -it --rm cpp-timsort ./build/TimSortMain
   ```

These commands will build and run the TimSort implementation in a containerized environment, allowing for easy execution and testing without the need for local setup.
## Testing

The project includes a comprehensive test suite using Google Test. The tests cover various scenarios including:

- Sorting random data of various sizes
- Sorting already sorted data
- Sorting reverse sorted data
- Handling data with many duplicates
- Sorting data with few unique values
- Edge cases such as empty vectors and vectors with a single element

To run the tests, use the `TestRunner` executable as described in the [Building and Running](#building-and-running) section.

## Function Overview

Here's a detailed overview of the main functions in the TimSort implementation:

### `timsort`
The main function that implements the TimSort algorithm. It orchestrates the entire sorting process by identifying runs, performing small sorts, and merging runs. This function handles the high-level logic of the algorithm, ensuring that the input array is efficiently sorted using a combination of techniques.

### `compute_minrun`
Calculates the minimum run length for efficient sorting. This function is crucial for optimizing the performance of TimSort. It determines an ideal minimum run size based on the input array's length, balancing the trade-off between the number of runs and the efficiency of merging.

### `count_run`
Identifies and counts the length of natural runs in the input. A "run" is a sequence of elements that are already in order (either ascending or descending). This function detects these naturally occurring ordered sequences, which TimSort then uses to its advantage. It also handles the case of descending runs by reversing them in-place.

### `binary_insertion_sort`
Used for sorting small runs efficiently. When a run is smaller than the minimum run size, this function is used to extend it. Binary insertion sort is chosen for its efficiency on small arrays and partially sorted sequences. It uses binary search to find the correct insertion point for each element, minimizing the number of comparisons.

### `merge_lo` and `merge_hi`
These are merge functions optimized for different scenarios. `merge_lo` is used when the first run is smaller than the second, while `merge_hi` is used when the second run is smaller. This optimization reduces the amount of memory needed for merging and improves cache efficiency.

### `gallop`
Implements the galloping mode for efficient merging of runs. When one run is consistently "winning" during a merge, this function allows the algorithm to skip over large portions of that run. This significantly speeds up the merging process in cases where there are large disparities between the runs being merged.

### `merge_collapse`
Maintains the invariants of the algorithm by merging runs when necessary. This function ensures that the lengths of the runs on the stack maintain a certain relationship, which is key to the efficiency of TimSort. It decides when and which runs to merge based on their lengths, maintaining a balance that leads to optimal overall performance.

### `reverse_range`
A utility function that reverses a range of elements in the array in-place. This is used when a descending run is detected, to convert it into an ascending run without using additional memory.

### `merge_at`
Merges two adjacent runs. This function decides whether to use `merge_lo` or `merge_hi` based on the lengths of the runs being merged, ensuring the most efficient merge strategy is used.

Each of these functions plays a crucial role in making TimSort efficient and robust across a wide range of input distributions. They work together to create an algorithm that adapts to the characteristics of the input data, combining the strengths of merge sort and insertion sort.

## Contributing

Contributions to improve the implementation or extend the documentation are welcome. Please feel free to submit issues or pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Tim Peters for the original TimSort algorithm and detailed documentation
- The C++ community for continuous inspiration and support
