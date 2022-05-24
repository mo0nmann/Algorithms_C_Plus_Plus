#include <iostream> 
#include <vector>
#include <random>
#include <algorithm> 
  
#include "../helpers.hpp"

// bogosort algorithm
void bogoSort(std::vector<int> *vec) {

    auto rng = std::default_random_engine {};

    // while not sorted
    while (!std::is_sorted(vec->begin(), vec->end())) {
        
        // randomise order of shuffle
        std::shuffle(vec->begin(), vec->end(), rng);
    }

}

int main() {
    
    int vector_size;

    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> vector_size;
    
    // generate random numbers
    std::vector<int> unsorted_vector = genRndVector(vector_size);
    std::vector<int> sorted_vector = unsorted_vector;

    // bogosort
    bogoSort(&sorted_vector);

    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}