#include <iostream>
#include <vector>

namespace pluto {

    namespace sorting {
    
        // bubble sort algorithm
        void bubbleSort(std::vector<int> *vec) {

            bool ordered = false;

            for (int i = 0; (i < vec->size()) && (!ordered); i++) {
                ordered = true;
                for (int j = 0; j < vec->size() - i - 1; j++) {
                    
                    if (vec->at(j) > vec->at(j + 1)) {
                        std::swap(vec->at(j), vec->at(j + 1));
                        ordered = false;
                    }
                }
            }
        }
    }
}


