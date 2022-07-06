#include <iostream> 
#include <vector>
#include <random>
#include <algorithm> 

namespace pluto {

    namespace sorting {

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
    }
}