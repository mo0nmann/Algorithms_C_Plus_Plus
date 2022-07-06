#include <iostream> 
#include <vector>
#include <random>
#include <algorithm> 

namespace pluto {

    namespace sorting {

        // bogosort algorithm
        void bogoSort(std::vector<int> *vec) {

            auto rng = std::default_random_engine {};

            // while not sorted
            while (!std::is_sorted(vec->begin(), vec->end())) {
                
                // randomise order of shuffle
                std::shuffle(vec->begin(), vec->end(), rng);
            }
        }
    }
}