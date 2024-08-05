#include "timsort.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>






int main() {
    size_t size =211111; // Size of the random dataset
    std::vector<int> data = generate_random_data(size);
    if(std::is_sorted(data.begin(),data.end())){
        std::cout<<"True at start"<<std::endl;
    }
    else{
        std::cout<<"False at start"<<std::endl;
    }
    timsort(data);
    if(std::is_sorted(data.begin(),data.end())){
        std::cout<<"True after sort"<<std::endl;
    }
    else{
        std::cout<<"False after sort"<<std::endl;
    }
    return 0;
}
