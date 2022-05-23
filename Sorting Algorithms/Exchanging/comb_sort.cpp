#include <random> 
#include <algorithm> 
#include <iterator> 
#include <iostream> 
#include <vector> 
  
/* returns a vector of given size with random 
   elements between -100 and 100            */ 
std::vector<int> genRndVector(int vector_size) { 
  
    std::random_device rnd_device; 
    std::mt19937 mersenne_engine {rnd_device()}; 
    std::uniform_int_distribution<int> dist {-100, 100}; 
  
    auto gen = [&dist, &mersenne_engine](){ 
        return dist(mersenne_engine); 
    }; 
  
    std::vector<int> vec(vector_size); 
    std::generate(vec.begin(), vec.end(), gen); 
  
    return vec; 
} 
  
/* function to print a comparison of the 
   unsorted and sorted vector         */ 
void printComparison(std::vector<int> unsorted_vector, std::vector<int> sorted_vector) { 
  
    std::cout << "Before: ["; 
    for (int i = 0; i < unsorted_vector.size(); i++) { 
        if (i != 0) { 
           std::cout << ", "; 
        } 
        std::cout << unsorted_vector[i]; 
    } 
    std::cout << "]" << std::endl; 
 

    std::cout << "After: ["; 
    for (int i = 0; i < sorted_vector.size(); i++) { 
        if (i != 0) { 
            std::cout << ", "; 
        }
 
        std::cout << sorted_vector[i]; 
    } 
    std::cout << "]" << std::endl; 
}

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

        for (int i = 0; i < vec->size() - gap; i++) {
            if (vec->at(i) > vec->at(i + gap)) {
                std::swap(vec->at(i), vec->at(i + gap));
                ordered = false;
            }
        } 
    }
}

int main() { 
 
    int vector_size; 
  
    std::cout << "Enter the amount of numbers to sort: "; 
    std::cin >> vector_size; 

    // generate random numbers 
    std::vector<int> unsorted_vector = genRndVector(vector_size); 
    std::vector<int> sorted_vector = unsorted_vector;
    
    // cocktail shaker sort
    combSort(&sorted_vector);
    
    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}
    