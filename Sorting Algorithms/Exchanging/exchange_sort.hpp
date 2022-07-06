#include <iostream> 
#include <vector> 

namespace pluto {

    namespace sorting {
    
        // exchange sort algorithm
        void exchangeSort(std::vector<int> *vec) {

            for (int i = 0; i < vec->size() - 1; i++) {
                for (int j = i + 1; j < vec->size(); j++) {
                    if (vec->at(i) > vec->at(j)) {
                        std::swap(vec->at(i), vec->at(j));
                    }
                }
            }
        }
    }
}
    