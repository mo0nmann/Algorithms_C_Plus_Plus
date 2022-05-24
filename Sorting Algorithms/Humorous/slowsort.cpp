#include <iostream> 
#include <vector>
  
#include "../helpers.hpp"

// slowsort algorithm
void slowsort(std::vector<int> *vec, int low, int high) {

    // base case
    if (low >= high) {
        return;
    }

    // middle value    
    int mid = low + (high - low) / 2;

    // recursively call with left half
    slowsort(vec, low, mid);

    // recursively call with right half
    slowsort(vec, mid + 1, high);

    // swap
    if (vec->at(high) < vec->at(mid)) {
        std::swap(vec->at(high), vec->at(mid));
    }

    // recursively call with whole array except max element
    slowsort(vec, low, high - 1);

}

int main() {
    
    int vector_size;

    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> vector_size;
    
    // generate random numbers
    std::vector<int> unsorted_vector = genRndVector(vector_size);
    std::vector<int> sorted_vector = unsorted_vector;

    // slowsort
    slowsort(&sorted_vector, 0, sorted_vector.size() - 1);

    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}