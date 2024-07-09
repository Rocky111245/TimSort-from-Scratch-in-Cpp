#include "timsort.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>






int main() {
    size_t size =2112; // Size of the random dataset
    std::vector<int> data = generate_random_data(size);
    timsort(data);
    if(std::is_sorted(data.begin(),data.end())){
        std::cout<<"True"<<std::endl;
    }
    else{
        std::cout<<"False"<<std::endl;
    }
    return 0;
}
