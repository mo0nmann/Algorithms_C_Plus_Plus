#include <iostream>
#include <vector>

namespace pluto {

    namespace sorting {

        // insertion sort algorithm
        void insertionSort(std::vector<int> *vec) {

            int key, j;

            // move from the second element to the last
            for (int i = 1; i < vec->size(); i++) {

                // hold the element that we want to compare and
                // potentially insert into the correct place
                key = vec->at(i);

                // move each element on the left of the key that 
                // is larger to the right                     
                for (j = i - 1; j >= 0 && vec->at(j) > key; j--) {
                    vec->at(j + 1) = vec->at(j);
                }

                // insert the element into it's correct position
                vec->at(j + 1) = key;
            }
            
        }
    }
}