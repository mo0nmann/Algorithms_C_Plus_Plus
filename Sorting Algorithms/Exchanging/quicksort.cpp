#include <iostream> 
#include <vector> 
  
#include "../helpers.hpp"

/* sets the median of the low, middle and high values to
   be stored at vec[high], and also sorts the three points */
void medianThree(std::vector<int> *vec, int low, int high) {

    int mid = low + (high - low) / 2;

    // sort mid and low
    if (vec->at(mid) < vec->at(low)) {
        std::swap(vec->at(mid), vec->at(low));
    } 

    // sort high and low
    if (vec->at(high) < vec->at(low)) {
        std::swap(vec->at(high), vec->at(low));
    } 

    // sort mid and high
    if (vec->at(mid) < vec->at(high)) {
        std::swap(vec->at(mid), vec->at(high));
    }
}

int partition(std::vector<int> *vec, int low, int high) {

    // perform median of three and set the pivot
    medianThree(vec, low, high);
    int pivot = vec->at(high);
    
    // set pivot index to lowest point
    int i = low;

    // loop through the partition
    for (int j = low; j < high; j++) {
        
        /* if the current element is less than or equal to the pivot
           swap the current element with the element at the pivot 
           index and move the pivot index forward                 */
        if (vec->at(j) <= pivot) {
            std::swap(vec->at(i), vec->at(j));
            i++;
        }
    }

    /* swap pivot with element at partition index. This element is
       the last element to be swapped. Then return the index    */
    std::swap(vec->at(i), vec->at(high));
    
    return i;
}


// quicksort algorithm
void quicksort(std::vector<int> *vec, int low, int high) {

    // base condition
    if (low < high) {

        // partition the vector and obtain the pivot index
        int pIndex = partition(vec, low, high);
        
        // sort to the left of the pivot
        quicksort(vec, low, pIndex - 1);

        // sort to the right of the pivot
        quicksort(vec, pIndex + 1, high);
    }
}

int main() { 
 
    int vector_size; 
  
    std::cout << "Enter the amount of numbers to sort: "; 
    std::cin >> vector_size; 

    // generate random numbers 
    std::vector<int> unsorted_vector = genRndVector(vector_size); 
    std::vector<int> sorted_vector = unsorted_vector;
    
    // quicksort
    quicksort(&sorted_vector, 0, sorted_vector.size() - 1);
    
    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}
    