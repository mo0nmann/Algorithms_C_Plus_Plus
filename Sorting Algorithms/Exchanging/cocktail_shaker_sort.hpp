#include <iostream> 
#include <vector>

namespace pluto {

    namespace sorting {
   
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
    }
}