#include <iostream> 
#include <vector> 

namespace pluto {

    namespace sorting {
    
        // odd-even sort algorithm
        void oddEvenSort(std::vector<int> *vec) {

            bool sorted = false;

            while (!sorted) {
                
                sorted = true; 

                // Bubble sort on odd indices
                for (int i = 1; i < vec->size() - 1; i += 2) {
                    if (vec->at(i) > vec->at(i + 1)) {
                        std::swap(vec->at(i), vec->at(i + 1));
                        sorted = false;
                    }
                }

                // Bubble sort on even indices
                for (int i = 0; i < vec->size() - 1; i += 2) {
                    if (vec->at(i) > vec->at(i + 1)) {
                        std::swap(vec->at(i), vec->at(i + 1));
                        sorted = false;
                    }
                }
            }
        }
    }
}
