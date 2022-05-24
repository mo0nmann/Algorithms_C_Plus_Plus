#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

/* returns a vector of given size with random
   elements between -100 and 100            */
std::vector<int> genRndVector(int vector_size) {

    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::uniform_int_distribution<int> dist {-100, 100};

    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };

    std::vector<int> vec(vector_size);
    std::generate(vec.begin(), vec.end(), gen);

    return vec;
}

/* function to print a comparison of the
   unsorted and sorted vector         */
void printComparison(std::vector<int> unsorted_vector, std::vector<int> sorted_vector) {

    std::cout << "Before: [";
    for (int i = 0; i < unsorted_vector.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << unsorted_vector[i];
    }
    std::cout << "]" << std::endl;

    
    std::cout << "After: [";
    for (int i = 0; i < sorted_vector.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << sorted_vector[i];
    }
    std::cout << "]" << std::endl;
}