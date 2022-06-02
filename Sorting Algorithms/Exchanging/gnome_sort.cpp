#include <iostream> 
#include <vector> 
  
#include "../helpers.hpp"

// gnome sort algorithm
void gnomeSort(std::vector<int> *vec) {

    int position = 0;
    
    while (position < vec->size()) {

        // if at the beginning or the next element is correctly ordered,
        // move to the next position                                  
        if (position == 0 || vec->at(position) >= vec->at(position - 1)) {
            position++;
        // otherwise swap
        } else {
            std::swap(vec->at(position), vec->at(position - 1));
            if (position > 1) {
                position--;
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
   
    // gnome sort
    gnomeSort(&sorted_vector);

    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}
    