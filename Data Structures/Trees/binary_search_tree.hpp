#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
#include <functional>

template <class T>
class binary_search_tree {
    private:
        
        // tree node
        struct bst_node {

            // value stored at node
            T value;

            /* include a variable to keep count of
               how many of this value there are. That way
               we can have duplicates values in the tree */
            int value_count;

            // pointers to children and parents
            bst_node *left;
            bst_node *right;
            bst_node *parent;

            // node constructor
            explicit bst_node(T value) {
                this->value = value;
                value_count = 1;
                left = nullptr;
                right = nullptr;
                parent = nullptr;
            }
        };

        // pointer to the root
        bst_node *root;

        // number of nodes
        int amount_of_nodes;

        // searches for given balue in bst
        bst_node * search(T value);

        // calculate max value from given node
        bst_node * maximum(bst_node *node);

        // calculate min value from given node
        bst_node * minimum(bst_node *node);

        // calculate successor from given node
        bst_node * successor(bst_node *node);

        // calculate predescessor from given node
        bst_node * predecessor(bst_node *node);

        // helper function to replace node u with node v
        void shift_nodes(bst_node *u, bst_node *v);

        /* traverses the bst in pre-order order, visiting node, left, then right. 
           The */
        void preorder_traversal(bst_node *node, std::function<void(T)> callback);
        
        void inorder_traversal(bst_node *node, std::function<void(T)> callback);

        void postorder_traversal(bst_node *node, std::function<void(T)> callback);

        // function to recursively clear nodes from memory
        void delete_recursive(bst_node *node);

    public:
        binary_search_tree();
        binary_search_tree(T value);
        binary_search_tree(std::vector<T> &values);

        ~binary_search_tree();

        // indicates whether given value is within bst
        bool contains_value(T value);

        T bst_max();
        T bst_min();

        bool insert(T value);
        bool remove(T value);

        int node_count();
        
        std::vector<T> get_elements_preorder();
        std::vector<T> get_elements_inorder();
        std::vector<T> get_elements_postorder();

        
};

// create empty BST
template<class T>
binary_search_tree<T>::binary_search_tree() {
    root = nullptr;
    amount_of_nodes = 0;
}

// create single node BST
template<class T>
binary_search_tree<T>::binary_search_tree(T value) {
    root = new bst_node(value);
    amount_of_nodes = 1;
}

// create BST from a vector of values
template<class T>
binary_search_tree<T>::binary_search_tree(std::vector<T> &values) {
    
    // set the node first
    root = new bst_node(values[0]);
    amount_of_nodes = 1;

    // iterate over all but first value and insert them
    typename std::vector<T>::iterator it;
    for (it = values.begin() + 1; it != values.end(); it++) {
        insert(*it);
    }

}

template<class T>
binary_search_tree<T>::~binary_search_tree()
{
    delete_recursive(root);
}


template<class T>
void binary_search_tree<T>::delete_recursive(bst_node *node) {

    if (node) {
        delete_recursive(node->left);
        delete_recursive(node->right);
        delete node;
        node = NULL;
    }

}

// iterative search find element in BST. Returns nullptr if not found
template<class T>
typename binary_search_tree<T>::bst_node * binary_search_tree<T>::search(T value) {

    // return nullptr if empty bst
    if (root == nullptr) {
        return root;
    }

    // create raw ptr for searching, pointing to root
    bst_node *temp = root;

    // iteratively search the bst
    while (value != temp->value) {

        if (value < temp->value) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }

        // return nullptr if not found
        if (temp == nullptr) {
            return temp;
        }
        
    }

    // return value if found
    return temp;
}

// returns whether the value is in the bst or not
template<class T>
bool binary_search_tree<T>::contains_value(T value) {

    if (search(value) == nullptr) {
        return false;
    } else {
        return true;
    }
}

// find node with the maximum value from the given node
template<class T>
typename binary_search_tree<T>::bst_node * binary_search_tree<T>::maximum(bst_node *node) {

    bst_node *temp = node;

    while (temp->right != nullptr) {
        temp = temp->right;
    }

    return temp;
}

// find node with the minimum value from the given root
template<class T>
typename binary_search_tree<T>::bst_node * binary_search_tree<T>::minimum(bst_node *node) {
    
    bst_node *temp = node;

    while (temp->left != nullptr) {
        temp = temp->left;
    }

    return temp;
}

/* calculate the successor of a given node.
   The successor is the node with the smallest
   value greater than the given node.
   (If all values are placed in order, 
   it will be the value directly after it)   */
template<class T>
typename binary_search_tree<T>::bst_node * binary_search_tree<T>::successor(bst_node *node) {

    // return the leftmost child of the right child
    if (node->right != nullptr) {
        return minimum(node);
    } 

    bst_node *temp = node;
    bst_node *parent_node = node->parent;

    // navigate up the parent ancestor nodes
    while(parent_node != nullptr && temp == parent_node->right) {
        temp = parent_node;
        parent_node = parent_node->parent;
    }

    return parent_node;
}

/* calculate the predecessor of a given node.
   The predecessor is the node with the largest
   value smaller than the given node
   (If all values are placed in order, 
   it will be the value directly before it)   */
template<class T>
typename binary_search_tree<T>::bst_node * binary_search_tree<T>::predecessor(bst_node *node) {

    // return the rightmost child of the left child
    if (node->left != nullptr) {
        return maximum(node);
    }
    
    bst_node *temp = node;
    bst_node *parent_node = node->parent;

    // navigate up the parent ancestor nodes
    while (parent_node != nullptr && node == parent_node->left) {
        temp = parent_node;
        parent_node = parent_node->parent;
    }

    return parent_node;
}

// returns the value of the maximum value in the bst
template<class T>
T binary_search_tree<T>::bst_max() {
    return maximum(root)->value;
}

// returns the value of the minimum value in the bst
template<class T>
T binary_search_tree<T>::bst_min() {
    return minimum(root)->value;
}

// inserts a new node into the bst
template<class T>
bool binary_search_tree<T>::insert(T value) {

    // if the tree is empty just create the node
    if (root == nullptr) {
        root = new bst_node(value);
        
    // if a root already exists
    } else {

        bst_node *existing_node = search(value);

        // if the value already exists in the tree, just increment the count
        if (existing_node != nullptr) {

            amount_of_nodes++;
            existing_node->value_count++;

            return true;
        }

        // create the new node
        bst_node* new_node = new bst_node(value);
        
        // set current node to root
        bst_node* current_node = root;

        // keep a pointer to the previous node
        bst_node* prev_node = nullptr;

        // iteratively traverse the tree
        while (current_node != nullptr) {

            prev_node = current_node;

            // lower values to the left, higher values to the right
            if (value < current_node->value) {
                current_node = current_node->left;
            } else {
                current_node = current_node->right;
            }
        }

        // assign the pointer to the parent
        new_node->parent = prev_node;

        // create pointer to current node for parent
        if (value < prev_node->value) {
            prev_node->left = new_node;
        } else {
            prev_node->right = new_node;
        }
    }

    amount_of_nodes++;
    return true;
}

// helper function to replace node u with v in the bst
template<class T>
void binary_search_tree<T>::shift_nodes(bst_node *u, bst_node *v) {

    if (u == nullptr) {
        return;
    }

    // if u is the root node, set v as the root node
    if (u->parent == nullptr) {
        root = v;

    // if u is to the left of it's parent
    } else if (u == u->parent->left) {
        u->parent->left = v;
    // if u is to the right of it's parent
    } else {
        u->parent->right = v;
    }
    
    // make u's parent v's parent
    if (v != nullptr) {
        v->parent = u->parent;
    }
    
}

// removes node with matching value
template<class T>
bool binary_search_tree<T>::remove(T value) {

    // find the node
    bst_node *current_node = search(value);

    // if value is not found, return
    if (current_node == nullptr) {
        return false;
    }

    int node_occurrences = current_node->value_count;

    /* make a copy of the node to be removed so we can
       delete it from memory afterwards */
    bst_node *copy = current_node;

    /* if the current node doesn't have a left child
       then we can replace it with it's right child.
       If it doesn't have a right child it gets set 
       to nullptr, effectively removing it from the bst */
    if (current_node->left == nullptr) {
        shift_nodes(current_node, current_node->right);

    /* otherwise, if it doesn't have a right child,
       replace it with it's left child. If it doesn't 
       have a left child it gets set to nullptr,
       effectively removing it from the bst        */
    } else if (current_node->right == nullptr) {
        shift_nodes(current_node, current_node->left);
    
    /* if the current node has two children, then it's
       successor takes it's position                */
    } else {
        
        // find successor
        bst_node *succ = successor(current_node);

        /* if the successor isn't the current 
           nodes immediate child */
        if (succ->parent != current_node) {

            // replace successor with it's right child
            shift_nodes(succ, succ->right);
            succ->right = current_node->right;
            succ->right->parent = succ;
        }

        // replace current node with the successor
        shift_nodes(current_node, succ);
        succ->left = current_node->left;
        succ->left->parent = succ;
    }

    // delete the node from memory
    delete copy;
    copy = NULL;

    amount_of_nodes -= node_occurrences;
    return true;
    
}

// return how many nodes there are in the bst
template<class T>
int binary_search_tree<T>::node_count() {
    return amount_of_nodes;
}

// traverse the tree in preorder fashion. Visit the node, then left, then right.
template<class T>
void binary_search_tree<T>::preorder_traversal(bst_node *node, std::function<void(T)> callback) {

    if (node == nullptr) {
        return;
    }

    // take into account each occurance of the element
    for (int i = 0; i < node->value_count; i++) {
        // invokes elements.push_back(node->value)
        callback(node->value);
    }    
    preorder_traversal(node->left, callback);
    preorder_traversal(node->right, callback);
}

// traverse the tree in inorder fashion. Visit the left, then the node, then the right.
template<class T>
void binary_search_tree<T>::inorder_traversal(bst_node *node, std::function<void(T)> callback) {

    if (node == nullptr) {
        return;
    }

    inorder_traversal(node->left, callback);
    for (int i = 0; i < node->value_count; i++) {
        callback(node->value);
    }    
    inorder_traversal(node->right, callback);
}

// traverse the tree in postorder fashion. Visit the left, then right, then the node
template<class T>
void binary_search_tree<T>::postorder_traversal(bst_node *node, std::function<void(T)> callback) {

    if (node == nullptr) {
        return;
    }

    postorder_traversal(node->left, callback);
    postorder_traversal(node->right, callback);
    for (int i = 0; i < node->value_count; i++) {
        callback(node->value);
    }    
}

// store elements of bst into a vector in preorder order
template<class T>
std::vector<T> binary_search_tree<T>::get_elements_preorder() {
    std::vector<T> elements;

    /* call preorder_traversal and pass elements.push_back(node_value)
       as a lambda function. This way this function can be called
       in preorder_traversal via the std::function<void(int)> callback */
    preorder_traversal(root, [&](T node_value) {
        elements.push_back(node_value);
    });

    return elements;
}

// store elements of bst into a vector in inorder order
template<class T>
std::vector<T> binary_search_tree<T>::get_elements_inorder() {
    std::vector<T> elements;

    inorder_traversal(root, [&](T node_value) {
        elements.push_back(node_value);
    });

    return elements;
}

// store elements of bst into a vector in postorder order
template<class T>
std::vector<T> binary_search_tree<T>::get_elements_postorder() {
    std::vector<T> elements;

    postorder_traversal(root, [&](T node_value) {
        elements.push_back(node_value);
    });

    return elements;
}