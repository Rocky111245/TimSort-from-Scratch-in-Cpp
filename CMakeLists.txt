cmake_minimum_required(VERSION 3.26)
project(TimSort_from_Scratch_in_Cpp)

set(CMAKE_CXX_STANDARD 23)

# Include the FetchContent module
include(FetchContent)

# Download and configure Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0  # Use the latest stable release
)

FetchContent_MakeAvailable(googletest)

# Add the executable for your main program
add_executable(TimSortMain main.cpp timsort.cpp)

# Add the executable for your tests
add_executable(TestRunner test.cpp timsort.cpp)

# Link the Google Test libraries with your test executable
target_link_libraries(TestRunner gtest gtest_main)
