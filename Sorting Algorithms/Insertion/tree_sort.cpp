#include <iostream>
#include <vector>

#include "../helpers.hpp"
#include "../../Data Structures/Trees/binary_search_tree.hpp"

// tree sort algorithm
void treeSort(std::vector<int> *vec) {

    BinarySearchTree<int> tree(*vec);

    vec->clear();
    tree.applyInorder([&](int node_value){
        vec->push_back(node_value);
    });    
}

int main() { 

    int vector_size; 
  
    std::cout << "Enter the amount of numbers to sort: "; 
    std::cin >> vector_size; 

    // generate random numbers 
    std::vector<int> unsorted_vector = genRndVector(vector_size); 
    std::vector<int> sorted_vector = unsorted_vector;
   
    // gnome sort
    treeSort(&sorted_vector);

    // output
    printComparison(unsorted_vector, sorted_vector);
    
    return 0;
}