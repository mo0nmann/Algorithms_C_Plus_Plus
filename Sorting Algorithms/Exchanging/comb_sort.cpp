#include <iostream> 
#include <vector> 
  
#include "../helpers.hpp"

// comb sort algorithm
void combSort(std::vector<int> *vec) {

    // declare shrink factor and gap
    // determine 1st gap in 1st loop iteration
    double shrink_factor = 1.3;
    int gap = vec->size();

    bool ordered = false;

    while (gap != 1 || !ordered) {

        // determine gap
        gap = (int) (gap / shrink_factor);
        if (gap < 1) {
            gap = 1;
        }

        ordered = true;

        for (int i = 0; i < vec->size() - gap; i++) {
            if (vec->at(i) > vec->at(i + gap)) {
                std::swap(vec->at(i), vec->at(i + gap));
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
    
    // comb sort
    combSort(&sorted_vector);
    
    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}
    