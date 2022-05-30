#include <iostream>
#include <vector>
#include <algorithm>

#include "../helpers.hpp"

/* the minimum value of int32. This
   algorithm will not work if this 
   value is in the vector to be sorted */
#define EMPTY -2147483648

// function to create the gapped vector with gaps of size ε
std::vector<int> createGappedVector(std::vector<int> *vec, int epsilon) {

    int n = vec->size();

    // calculate size of gapped vector
    // with gaps of size ε
    int S_size = (1 + epsilon) * n;

    // create the gapped vector and fill it with -2,147,483,648
    std::vector<int> S(S_size);
    std::fill(S.begin(), S.end(), EMPTY);

    // place elements of unsorted vector in gapped positions
    for (int i = 0; i < n; i++) {
        S[((1 + epsilon) * i) + epsilon] = vec->at(i);
    }

    return S;
}

/* performs binary search on the first k elements of S,
   skipping over gaps, to find a place for the element.
   Insertion should favor gaps over filled-in elements */   
int binarySearch(int element, std::vector<int> *S, int k) {

    // binary search
    int low = 0;
    int high = k;
    while (high > low + 1) {

        // mid = (low + high) / 2
        int mid = (low + high) >> 1;

        if (S->at(mid) != EMPTY) {
            if (S->at(mid) < element) {
                low = mid;
            } else {
                high = mid;
            }
        } else {
            
            int left = mid - 1;
            int right = mid + 1;
            
            // look for non-empty element to the left
            while (S->at(left) == EMPTY && left > 0) {
                left--;
            }
            
            // look for non-empty element to the right
            while (S->at(right) == EMPTY && right < S->size()) {
                right++;
            }

            if (S->at(left) > element) {
                high = left;
            } else if (S->at(right) < element) {
                low = right;
            } else {
                low = left;
                high = right;
                break;
            }
        }   
    }

    if (high > low + 1) {
        return (low + high) >> 1;
    } else {

        /* if the found element is not a gap
           we will handle the sorting /  placement
           in here and return -1            */
        if (S->at(low) != EMPTY) {

            if (S->at(low) > element) {
                high = low;
            }

            // insert the element and move everything to the right
            while (element != EMPTY) {
                std::swap(S->at(high), element);
                high++;
            }
            
            return -1;

        } else {
            return low;
        }
    }

}

/* function to rebalance the gapped array and place ε gaps
   inbetween each element */
void rebalance(std::vector<int> *S, int begin, int end, int epsilon) {

    int r = end;
    
    while (r >= begin) {
        if (S->at(r) != EMPTY) {
            std::swap(S->at(r), S->at(end));
            end -= (epsilon + 1);
        }
        r -= 1;
    }
}

// library sort sort algorithm
void librarySort(std::vector<int> *vec, int epsilon) {

    // create gapped vector
    std::vector<int> S = createGappedVector(vec, epsilon);

    int n = vec->size();

    int a = 1;
    int b = 2;

    // for i to floor(log2(n) + 1)
    for (int i = 0; i < floor(log2(n) + 1); i++) {
        
        // multiply a and b by 2
        a <<= 1;
        b <<= 1;

        int next_index, element_to_sort = 0;
       
        for (int j = a; j < std::min(b, n + 1); j++) {

            // get next element to sort in S
            next_index = ((1 + epsilon) * j) - 1;
            element_to_sort = S[next_index];
            
            // find position for insertion
            int insert_pos = binarySearch(element_to_sort, &S, next_index);
        
            // insert
            if (insert_pos >= 0) {
                S[insert_pos] = element_to_sort;
            }

            // set old position to empty
            S[next_index] = EMPTY;
            
        }
        
        // rebalance
        rebalance(&S, 0, next_index, epsilon);  

    }

    // clear the original array and place all non gap elements in it
    vec->clear();
    std::copy_if(S.begin(), S.end(), std::back_inserter(*vec), [](int x) {
        return x != EMPTY;
    });

}

int main() {
    
    int vector_size;
    int epsilon;

    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> vector_size;

    std::cout << "Enter the desired gap size, ε, (must be greater or equal to 1): ";
    std::cin >> epsilon;
    
    // generate random numbers
    std::vector<int> unsorted_vector = genRndVector(vector_size);
    std::vector<int> sorted_vector = unsorted_vector;

    // library sort sort with user inputted ε
    librarySort(&sorted_vector, epsilon);

    printComparison(unsorted_vector, sorted_vector);

    return 0;
}
