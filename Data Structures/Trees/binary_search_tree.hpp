#include <vector>
#include <iterator>
#include <functional>

template <class T>
class BinarySearchTree {
    protected:
        
        // tree node
        class Node {
            public:

            // value stored at node
            T value;

            // include a variable to keep count of
            // how many of this value there are. That way
            // we can have duplicates values in the tree
            int value_count;

            // pointers to children and parent
            Node *left;
            Node *right;
            Node *parent;

            // node constructor
            Node(T value); 
            ~Node();
        };

        // pointer to the root
        Node *root_;

        // number of nodes
        int amount_of_nodes_;

        // searches for given balue in bst
        Node * search(T value);

        // calculate max value from given node
        Node * maximum(Node *node);

        // calculate min value from given node
        Node * minimum(Node *node);

        // calculate successor from given node
        Node * successor(Node *node);

        // calculate predescessor from given node
        Node * predecessor(Node *node);

        // helper function to replace node u with node v
        void shiftNodes(Node *u, Node *v);

        // traverses the bst in pre-order order, visiting node, left, then right. 
        void preorderTraversal(Node *node, std::function<void(T)> callback);
        
        // traverses the bst inorder order, visiting the left, then the node, then right. 
        void inorderTraversal(Node *node, std::function<void(T)> callback);

        // traverses the bst in pre-order order, visiting the left, then right, then the node
        void postorderTraversal(Node *node, std::function<void(T)> callback);

        // function to recursively clear nodes from memory
        void deleteRecursive(Node *node);

    public:
        BinarySearchTree();
        BinarySearchTree(T value);
        BinarySearchTree(std::vector<T> &values);

        ~BinarySearchTree();

        // indicates whether given value is within bst
        bool containsValue(T value);

        T bstMax();
        T bstMin();

        void insert(T value);
        bool remove(T value);

        int nodeCount();
        
        // traverse the tree in preorder with a user defined lamda function
        void applyPreorder(std::function<void(T)> callback);

        // traverse the tree inorder with a user defined lamda function
        void applyInorder(std::function<void(T)> callback);

        // traverse the tree in postorder with a user defined lamda function
        void applyPostorder(std::function<void(T)> callback);

        
};

template<class T>
BinarySearchTree<T>::Node::Node(T value) {
    this->value = value;
    value_count = 1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<class T>
BinarySearchTree<T>::Node::~Node() {}

// create empty BST
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
    root_ = nullptr;
    amount_of_nodes_ = 0;
}

// create single node BST
template<class T>
BinarySearchTree<T>::BinarySearchTree(T value) {
    root_ = new Node(value);
    amount_of_nodes_ = 1;
}

// create BST from a vector of values
template<class T>
BinarySearchTree<T>::BinarySearchTree(std::vector<T> &values) {
    
    // set the node first
    root_ = new Node(values[0]);
    amount_of_nodes_ = 1;

    // iterate over all but first value and insert them
    typename std::vector<T>::iterator it;
    for (it = values.begin() + 1; it != values.end(); it++) {
        insert(*it);
    }

}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    deleteRecursive(root_);
}

// delete all pointers in the tree from memory
template<class T>
void BinarySearchTree<T>::deleteRecursive(Node *node) {

    if (node) {
        deleteRecursive(node->left);
        deleteRecursive(node->right);
        delete node;
        node = NULL;
    }

}

// iterative search find element in BST. Returns nullptr if not found
template<class T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::search(T value) {

    // return nullptr if empty bst
    if (root_ == nullptr) {
        return root_;
    }

    // create raw ptr for searching, pointing to root
    Node *temp = root_;

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
bool BinarySearchTree<T>::containsValue(T value) {
    return search(value) != nullptr;
}

// find node with the maximum value from the given node
template<class T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::maximum(Node *node) {

    Node *temp = node;

    while (temp->right != nullptr) {
        temp = temp->right;
    }

    return temp;
}

// find node with the minimum value from the given root
template<class T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::minimum(Node *node) {
    
    Node *temp = node;

    while (temp->left != nullptr) {
        temp = temp->left;
    }

    return temp;
}

// calculate the successor of a given node.
// The successor is the node with the smallest
// value greater than the given node.
// (If all values are placed in order, 
// it will be the value directly after it) 
template<class T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::successor(Node *node) {

    // return the leftmost child of the right child
    if (node->right != nullptr) {
        return minimum(node);
    } 

    Node *temp = node;
    Node *parent_node = node->parent;

    // navigate up the parent ancestor nodes
    while(parent_node != nullptr && temp == parent_node->right) {
        temp = parent_node;
        parent_node = parent_node->parent;
    }

    return parent_node;
}

// calculate the predecessor of a given node.
// The predecessor is the node with the largest
// value smaller than the given node
// (If all values are placed in order, 
// it will be the value directly before it)  
template<class T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::predecessor(Node *node) {

    // return the rightmost child of the left child
    if (node->left != nullptr) {
        return maximum(node);
    }
    
    Node *temp = node;
    Node *parent_node = node->parent;

    // navigate up the parent ancestor nodes
    while (parent_node != nullptr && node == parent_node->left) {
        temp = parent_node;
        parent_node = parent_node->parent;
    }

    return parent_node;
}

// returns the value of the maximum value in the bst
template<class T>
T BinarySearchTree<T>::bstMax() {
    return maximum(root_)->value;
}

// returns the value of the minimum value in the bst
template<class T>
T BinarySearchTree<T>::bstMin() {
    return minimum(root_)->value;
}

// inserts a new node into the bst
template<class T>
void BinarySearchTree<T>::insert(T value) {

    // if the tree is empty just create the node
    if (root_ == nullptr) {
        root_ = new Node(value);
        
    // if a root already exists
    } else {

        Node *existing_node = search(value);

        // if the value already exists in the tree, just increment the count
        if (existing_node != nullptr) {

            amount_of_nodes_++;
            existing_node->value_count++;

            return;
        }

        // create the new node
        Node* new_node = new Node(value);
        
        // set current node to root
        Node* current_node = root_;

        // keep a pointer to the previous node
        Node* prev_node = nullptr;

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

    amount_of_nodes_++;
}

// helper function to replace node u with v in the bst
template<class T>
void BinarySearchTree<T>::shiftNodes(Node *u, Node *v) {

    if (u == nullptr) {
        return;
    }

    // if u is the root node, set v as the root node
    if (u->parent == nullptr) {
        root_ = v;

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
bool BinarySearchTree<T>::remove(T value) {

    // find the node
    Node *current_node = search(value);

    // if value is not found, return
    if (current_node == nullptr) {
        return false;
    }

    int node_occurrences = current_node->value_count;

    // make a copy of the node to be removed so we can
    // delete it from memory afterwards 
    Node *copy = current_node;

    // if the current node doesn't have a left child
    // then we can replace it with it's right child.
    // If it doesn't have a right child it gets set 
    // to nullptr, effectively removing it from the bst 
    if (current_node->left == nullptr) {
        shiftNodes(current_node, current_node->right);

    // otherwise, if it doesn't have a right child,
    // replace it with it's left child. If it doesn't 
    // have a left child it gets set to nullptr,
    // effectively removing it from the bst        
    } else if (current_node->right == nullptr) {
        shiftNodes(current_node, current_node->left);
    
    // if the current node has two children, then it's
    // successor takes it's position                
    } else {
        
        // find successor
        Node *succ = successor(current_node);

        // if the successor isn't the current 
        // nodes immediate child
        if (succ->parent != current_node) {

            // replace successor with it's right child
            shiftNodes(succ, succ->right);
            succ->right = current_node->right;
            succ->right->parent = succ;
        }

        // replace current node with the successor
        shiftNodes(current_node, succ);
        succ->left = current_node->left;
        succ->left->parent = succ;
    }

    // delete the node from memory
    delete copy;
    copy = NULL;

    amount_of_nodes_ -= node_occurrences;
    return true;
    
}

// return how many nodes there are in the bst
template<class T>
int BinarySearchTree<T>::nodeCount() {
    return amount_of_nodes_;
}

// traverse the tree in preorder fashion. Visit the node, then left, then right.
template<class T>
void BinarySearchTree<T>::preorderTraversal(Node *node, std::function<void(T)> callback) {

    if (node == nullptr) {
        return;
    }

    // take into account each occurance of the element
    for (int i = 0; i < node->value_count; i++) {
        // invokes elements.push_back(node->value)
        callback(node->value);
    }    
    preorderTraversal(node->left, callback);
    preorderTraversal(node->right, callback);
}

// traverse the tree in inorder fashion. Visit the left, then the node, then the right.
template<class T>
void BinarySearchTree<T>::inorderTraversal(Node *node, std::function<void(T)> callback) {

    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left, callback);
    for (int i = 0; i < node->value_count; i++) {
        callback(node->value);
    }    
    inorderTraversal(node->right, callback);
}

// traverse the tree in postorder fashion. Visit the left, then right, then the node
template<class T>
void BinarySearchTree<T>::postorderTraversal(Node *node, std::function<void(T)> callback) {

    if (node == nullptr) {
        return;
    }

    postorderTraversal(node->left, callback);
    postorderTraversal(node->right, callback);
    for (int i = 0; i < node->value_count; i++) {
        callback(node->value);
    }    
}

// traverse the tree in preorder with a user defined lamda function
template<class T>
void BinarySearchTree<T>::applyPreorder(std::function<void(T)> callback) {
    preorderTraversal(root_, callback);
}

// traverse the tree inorder with a user defined lamda function
template<class T>
void BinarySearchTree<T>::applyInorder(std::function<void(T)> callback) {
    inorderTraversal(root_, callback);
}

// traverse the tree in postorder with a user defined lamda function
template<class T>
void BinarySearchTree<T>::applyPostorder(std::function<void(T)> callback) {
    postorderTraversal(root_, callback);
}