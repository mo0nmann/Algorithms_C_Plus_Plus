#include <iostream> 
#include <vector> 
  
#include "../helpers.hpp"

// odd-even sort algorithm
void oddEvenSort(std::vector<int> *vec) {

}

int main() { 
 
    int vector_size; 
  
    std::cout << "Enter the amount of numbers to sort: "; 
    std::cin >> vector_size; 

    // generate random numbers 
    std::vector<int> unsorted_vector = genRndVector(vector_size); 
    std::vector<int> sorted_vector = unsorted_vector;
    
    // odd-even sort
    oddEvenSort(&sorted_vector);
    
    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}
    