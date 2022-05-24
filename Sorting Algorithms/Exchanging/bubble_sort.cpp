#include <iostream>
#include <vector>

#include "../helpers.hpp"

// bubble sort algorithm
void bubbleSort(std::vector<int> *vec) {

    bool ordered = false;

    for (int i = 0; (i < vec->size()) && (!ordered); i++) {
        ordered = true;
        for (int j = 0; j < vec->size() - i - 1; j++) {
            
            if (vec->at(j) > vec->at(j + 1)) {
                std::swap(vec->at(j), vec->at(j + 1));
                ordered = false;
            }

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

    // bubble sort
    bubbleSort(&sorted_vector);

    // output
    printComparison(unsorted_vector, sorted_vector);
    

    return 0;
}