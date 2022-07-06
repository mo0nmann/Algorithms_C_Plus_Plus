#include <iostream> 
#include <vector> 

namespace pluto {

    namespace sorting {
    
        // gnome sort algorithm
        void gnomeSort(std::vector<int> *vec) {

            int position = 0;
            
            while (position < vec->size()) {

                // if at the beginning or the next element is correctly ordered,
                // move to the next position                                  
                if (position == 0 || vec->at(position) >= vec->at(position - 1)) {
                    position++;
                // otherwise swap
                } else {
                    std::swap(vec->at(position), vec->at(position - 1));
                    if (position > 1) {
                        position--;
                    }    
                }
            }

        }
    }
}