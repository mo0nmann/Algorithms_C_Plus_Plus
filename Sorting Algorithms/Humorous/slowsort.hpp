#include <iostream> 
#include <vector>

namespace pluto {

    namespace sorting {

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
    }
}