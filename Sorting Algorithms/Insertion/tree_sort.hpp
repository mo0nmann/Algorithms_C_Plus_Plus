#include <iostream>
#include <vector>

#include "../../Data Structures/Trees/binary_search_tree.hpp"

namespace pluto {

    namespace sorting {

        // tree sort algorithm
        void treeSort(std::vector<int> *vec) {

            pluto::data_structures::BinarySearchTree<int> tree(*vec);

            vec->clear();
            tree.applyInorder([&](int node_value){
                vec->push_back(node_value);
            });    
        }
    }
}