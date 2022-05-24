#include <iostream> 
#include <vector>
#include <random>
#include <algorithm> 
  
#include "../helpers.hpp"

// stooge sort algorithm
void stoogeSort(std::vector<int> *vec, int low, int high) {

    // base case
    if (low >= high) {
        return;
    }

    // If first element is smaller than
    // last element, swap them
    if (vec->at(low) > vec->at(high)){
        std::swap(vec->at(low), vec->at(high));
    }

    // If there are more than 2 elements
    // in the array
    if (high - low + 1 > 2) {
        int third = (high - low + 1) / 3;
 
        // Recursively sort the first
        // 2/3 elements
        stoogeSort(vec, low, high - third);
 
        // Recursively sort the last
        // 2/3 elements
        stoogeSort(vec, low + third, high);
 
        // Recursively sort the first
        // 2/3 elements again
        stoogeSort(vec, low, high - third);
    }

}

int main() {
    
    int vector_size;

    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> vector_size;
    
    // generate random numbers
    std::vector<int> unsorted_vector = genRndVector(vector_size);
    std::vector<int> sorted_vector = unsorted_vector;

    // stooge sort
    stoogeSort(&sorted_vector, 0, sorted_vector.size() - 1);

    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}