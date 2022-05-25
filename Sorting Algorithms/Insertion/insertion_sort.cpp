#include <iostream>
#include <vector>

#include "../helpers.hpp"

// insertion sort algorithm
void insertionSort(std::vector<int> *vec) {

    // move from the second element to the last
    for (int i = 1; i < vec->size(); i++) {

        // compare and swap with the previous element if it is larger
        for (int j = i; j > 0 && vec->at(j) < vec->at(j - 1); j--) {
            std::swap(vec->at(j), vec->at(j - 1));
        }
    }
    
}

int main() {
    
    int vector_size;

    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> vector_size;
    
    // generate random numbers
    std::vector<int> unsorted_vector = genRndVector(vector_size);
    std::vector<int> sorted_vector = unsorted_vector;

    // insertion sort
    insertionSort(&sorted_vector);
    // output
    printComparison(unsorted_vector, sorted_vector);
    

    return 0;
}