#include <iostream>
#include <vector>

namespace pluto {

    namespace sorting {

        // shell sort sort algorithm
        void shellSort(std::vector<int> *vec) {

            // Ciura gaps. Everything past 1750 is an extension via hₖ = ⌊2.25hₖ₋₁⌋ 
            // http://oeis.org/A102549
            std::vector <int> gaps = {
                149109795,
                66271020,
                29453787,
                13090572,
                5818032,
                2585792,
                1149241,
                510774,
                227011,
                100894,
                44842,
                19930,
                8858,
                3937,
                1750,
                701,
                301,
                132,
                57,
                23,
                10,
                4,
                1
            };

            int key, j;

            // for each gap
            for (int g = 0; g < gaps.size(); g++) {
                
                int gap = gaps[g];

                // move from the vec[gap] to the right
                for (int i = gap; i < vec->size(); i++) {

                    // hold the element that we want to compare and
                    //potentially insert into the correct place */
                    key = vec->at(i);

                    // check all elements to the left of the key that are a
                    // N gaps away. If they are larger than the key, move
                    // them N gaps to the right                          
                    for (j = i; j >= gap && vec->at(j - gap) > key; j-= gap) {
                        vec->at(j) = vec->at(j - gap);
                    }

                    // insert the element into it's correct position
                    vec->at(j) = key;
                }
            }    
        }
    }
}