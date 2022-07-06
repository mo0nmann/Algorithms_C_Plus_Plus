#include <iostream> 
#include <vector> 

namespace pluto {

    namespace sorting {
    
        // comb sort algorithm
        void combSort(std::vector<int> *vec) {

            // declare shrink factor and gap
            // determine 1st gap in 1st loop iteration
            double shrink_factor = 1.3;
            int gap = vec->size();

            bool ordered = false;

            while (gap != 1 || !ordered) {

                // determine gap
                gap = (int) (gap / shrink_factor);
                if (gap < 1) {
                    gap = 1;
                }

                ordered = true;

                // complete bubbling pass
                for (int i = 0; i < vec->size() - gap; i++) {
                    if (vec->at(i) > vec->at(i + gap)) {
                        std::swap(vec->at(i), vec->at(i + gap));
                        ordered = false;
                    }
                } 
            }
        }
    }
}