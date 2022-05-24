#include <iostream> 
#include <vector> 
  
#include "../helpers.hpp"

// exchange sort algorithm
void exchangeSort(std::vector<int> *vec) {

    for (int i = 0; i < vec->size() - 1; i++) {
        for (int j = i + 1; j < vec->size(); j++) {
            if (vec->at(i) > vec->at(j)) {
                std::swap(vec->at(i), vec->at(j));
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
    
    // exchange sort
    exchangeSort(&sorted_vector);
    
    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}
    