#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../helpers.hpp"

#define EMPTY INT32_MIN

std::vector<int> createGappedVector(int n, int epsilon) {

    // calculate size of gapped vector
    // with gaps of size ε
    int S_size = (1 + epsilon) * n;

    // create the gapped vector and fill it with -1
    std::vector<int> S(S_size);
    std::fill(S.begin(), S.end(), EMPTY);

    return S;
}

// binary search method to find a free spot for the element
int findFreeSpot(std::vector<int> *S, int element, int last) {
    
    int first = 0;
    int middle;
        
    while (last >= 0 && S->at(last) == EMPTY) {
        last--;
    }

    while (first <= last && S->at(first) == EMPTY) {
        first++;
    }
    
    // modified binary sort
    while (first <= last) {
        middle = (first + last) / 2;

        if (S->at(middle) == EMPTY) {

            int next_space = middle + 1;

            // move to the right
            while (next_space < last && S->at(next_space) == EMPTY) {
                next_space++;
            }

            if (S->at(next_space) > element) {
                
                next_space = middle - 1;

                // move to the left
                while (middle > first && S->at(middle) == EMPTY) {
                    middle--;
                }

                if (S->at(middle) < element) {
                    return middle;
                }

                last = middle - 1;

            } else {
                first = next_space + 1;
            }

        } else if (S->at(middle) < element) {
            first = middle + 1;
        } else {
            last = middle - 1;
        }
    }

    if (last >= 0 && S->at(last) == EMPTY) {
        last --;
    }
    return last;
}

void handleOccupiedPos(std::vector<int> *S, int *insert_pos, int S_size) {
    
    int ins_pos;
    ins_pos = *insert_pos;
    
    // if position is not empty
    if (S->at(ins_pos) != EMPTY) {
        
        // search for a free space to the right
        int next_free_space = ins_pos + 1;
        while (S->at(next_free_space) != EMPTY) {
            next_free_space++;
        }
        
        /* if no free spaces to the right
            (we hit the upper boundry)  */
        if (next_free_space >= S_size) {

            // search for a free space to the left
            next_free_space = ins_pos - 1;
            while (S->at(next_free_space) != EMPTY) {
                next_free_space--;
            }

            // shift all elements to the left
            while (next_free_space < ins_pos) {
                S->at(next_free_space) = S->at(next_free_space + 1);
                next_free_space++;
            }

        } else {
            // shift all elements to the right
            while (next_free_space > ins_pos) {
                S->at(next_free_space) = S->at(next_free_space - 1);
                next_free_space--;
            }
        }

    // if insert position is out of bounds
    } else if (ins_pos >= S_size) {
        
        insert_pos--;
        
        // search for a free space to the left
        int next_free_space = ins_pos - 1;
        while (S->at(next_free_space) != EMPTY) {
            next_free_space--;
        }

        // shift all elements to the left
        while (next_free_space < ins_pos) {
            S->at(next_free_space) = S->at(next_free_space + 1);
            next_free_space++;
        }
    }
}

// inserts spaces between each pair of elements in the vector
void rebalance(std::vector<int> *S, int initial_len, int final_len) {

    int k = final_len - 1;
    int step = final_len / initial_len;

    for (int i = initial_len - 1; i >= 0; i--) {        
        S->at(k) = S->at(i);
        S->at(i) = EMPTY;
        k -= step;
    } 
}

// copy all the elements in the gapped vector to the initial vector
void replaceInitialVector(std::vector<int> *vec, std::vector<int> *S, int S_size) {

    for (int i = 0, j = 0; i < S_size && j < vec->size(); i++) {
        if (S->at(i) != EMPTY) {
            vec->at(j) = S->at(i);
            j++;
        }
    }
}

// library sort sort algorithm
void librarySort(std::vector<int> *vec, int epsilon) {
    
    int n = vec->size();
    
    // create gapped vector
    std::vector<int> S = createGappedVector(n, epsilon);

    int goal = 1;    
    int pos = 1;

    S[0] = vec->at(0);

    int S_size = std::max(1 + epsilon, goal + 1);

    // loop through unsorted vector
    while (pos < n) {
        for (int i = 0; i < goal; i++) {
            
            // find insert position for vec[j] into S (search for an empty spot)      
            int insert_pos = findFreeSpot(&S, vec->at(pos), S_size - 1);
            
            insert_pos++;
            handleOccupiedPos(&S, &insert_pos, S_size);          

            // Insert the element and increment the position
            S[insert_pos] = vec->at(pos);
            pos++;

            // if we have inserted all elements, return
            if (pos >= n) {
                replaceInitialVector(vec, &S, S_size);
                return;
            }
        }
        
        int previous_size = S_size;
        S_size = std::min((2 + 2 * epsilon) * goal, (1 + epsilon) * n);
        
        rebalance(&S, previous_size, S_size);
        
        goal *= 2;
    }
}

int main() {
    
    int vector_size;

    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> vector_size;
    
    // generate random numbers
    std::vector<int> unsorted_vector = genRndVector(vector_size);
    std::vector<int> sorted_vector = unsorted_vector;

    // library sort sort with ε = 4
    librarySort(&sorted_vector, 4);
    
    // output
    printComparison(unsorted_vector, sorted_vector);
    

    return 0;
}
