#include <iostream> 
#include <vector> 
  
#include "../helpers.hpp"
  
// cocktail shaker sort
void cocktailShakerSort(std::vector<int> *vec) {

    bool sorted = false;

    int low = 0;
    int high = vec->size() - 1;

    while(!sorted) {
        
        sorted = true;

        // move from left to right
        for (int i = low; i < high; i++) {
            if (vec->at(i) > vec->at(i + 1)) {
                std::swap(vec->at(i), vec->at(i + 1));
                sorted = false;
            }
        }
        
        // if no swap was made, then it is sorted
        if (sorted) {
            break;
        }
        
        sorted = true;
        high--;
        
        // move from right to left
        for (int i = high - 1; i >= low; i--) {
            if (vec->at(i) > vec->at(i + 1)) {
                std::swap(vec->at(i), vec->at(i + 1));
                sorted = false;
            }
        }
        
        low++;
    }

}

int main() { 
 
    int vector_size; 
  
    std::cout << "Enter the amount of numbers to sort: "; 
    std::cin >> vector_size; 

    // generate random numbers 
    std::vector<int> unsorted_vector = genRndVector(vector_size); 
    std::vector<int> sorted_vector = unsorted_vector;
    
    // cocktail shaker sort
    cocktailShakerSort(&sorted_vector);
    
    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}
    
