#include <vector>
#include <iterator>
#include <functional>
#include <memory>

namespace pluto {

    namespace data_structures {

        template <class T>
        class BinarySearchTree {
            protected:
                
                // tree node
                struct TreeNode {

                    // value stored at node
                    T value;

                    // include a variable to keep count of
                    // how many of this value there are. That way
                    // we can have duplicates values in the tree
                    int value_count;

                    // pointers to children
                    std::unique_ptr<TreeNode> left;
                    std::unique_ptr<TreeNode> right;

                    int balance_factor;

                    // node constructor
                    explicit TreeNode(T value) {
                        this->value = value;
                        value_count = 1;
                        left = nullptr;
                        right = nullptr;
                        balance_factor = 0;
                    }
                };

                // pointer to the root
                std::unique_ptr<TreeNode> root_;

                // number of nodes
                int amount_of_nodes_;

                TreeNode * search(T value);

                TreeNode * maximum(std::unique_ptr<TreeNode> &node);
                TreeNode * minimum(std::unique_ptr<TreeNode> &node);

                TreeNode * successor(std::unique_ptr<TreeNode> &node);

                void recursiveInsert(std::unique_ptr<TreeNode> &node, T value);
                bool recursiveRemove(std::unique_ptr<TreeNode> &parent, std::unique_ptr<TreeNode> &node, T value);

                void preorderTraversal(std::unique_ptr<TreeNode> &node, std::function<void(T)> callback);
                void inorderTraversal(std::unique_ptr<TreeNode> &node, std::function<void(T)> callback);
                void postorderTraversal(std::unique_ptr<TreeNode> &node, std::function<void(T)> callback);

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

        // create empty BST
        template<class T>
        BinarySearchTree<T>::BinarySearchTree() {
            root_ = nullptr;
            amount_of_nodes_ = 0;
        }

        // create single node BST
        template<class T>
        BinarySearchTree<T>::BinarySearchTree(T value) {
            root_ = std::unique_ptr<TreeNode>(new TreeNode(value));
            amount_of_nodes_ = 1;
        }

        // create BST from a vector of values
        template<class T>
        BinarySearchTree<T>::BinarySearchTree(std::vector<T> &values) {
            
            // set the node first
            root_ = std::unique_ptr<TreeNode>(new TreeNode(values[0]));
            amount_of_nodes_ = 1;

            // iterate over all but first value and insert them
            typename std::vector<T>::iterator it;
            for (it = values.begin() + 1; it != values.end(); it++) {
                insert(*it);
            }

        }

        template<class T>
        BinarySearchTree<T>::~BinarySearchTree()
        {}

        // iterative search find element in BST. Returns nullptr if not found
        template<class T>
        typename BinarySearchTree<T>::TreeNode * BinarySearchTree<T>::search(T value) {
            
            TreeNode* temp = root_.get();
        
            // iteratively search the bst
            while (temp != nullptr && temp->value != value)
            {
                temp = (value < temp->value) ? temp->left.get() : temp->right.get();
            }

            return temp;

        }

        // returns whether the value is in the bst or not
        template<class T>
        bool BinarySearchTree<T>::containsValue(T value) {
            return search(value) != nullptr;
        }

        // find node with the maximum value from the given node
        template<class T>
        typename BinarySearchTree<T>::TreeNode * BinarySearchTree<T>::maximum(std::unique_ptr<TreeNode> &node) {

            TreeNode *temp = node.get();

            while (temp->right) {
                temp = temp->right.get();
            }

            return temp;
        }

        // find node with the minimum value from the given root
        template<class T>
        typename BinarySearchTree<T>::TreeNode * BinarySearchTree<T>::minimum(std::unique_ptr<TreeNode> &node) {
            
            TreeNode *temp = node.get();

            while (temp->left) {
                temp = temp->left.get();
            }

            return temp;
        }

        // calculate the successor of a given node.
        // The successor is the node with the smallest
        // value greater than the given node.
        // (If all values are placed in order, 
        // it will be the value directly after it) 
        template<class T>
        typename BinarySearchTree<T>::TreeNode * BinarySearchTree<T>::successor(std::unique_ptr<TreeNode> &node) {

            // base case
            if (!node) {
                return nullptr;
            }

            TreeNode *succ = nullptr;
            TreeNode *temp = root_.get();

            while (1) {

                // if value is less than node, visit
                if (node->value < temp->value) {

                    succ = temp;
                    temp = temp->left.get();
                
                } else if (node->value > temp->value) {
                    temp = temp->right.get();
                
                } else {
                    if (temp->right) {
                        succ = minimum(temp->right);
                    }
                    break;
                }

                if (temp == nullptr) {
                    return succ;
                }
            }

            return succ;

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
        void BinarySearchTree<T>::recursiveInsert(std::unique_ptr<TreeNode> &node, T value) {
            
            if (value < node->value) {
                
                if (!node->left) {
                    node->left = std::unique_ptr<TreeNode>(new TreeNode(value));
                    amount_of_nodes_++;
                } else {
                    recursiveInsert(node->left, value);
                }
            } else if (value > node->value) {
                if (!node->right) {
                    node->right = std::unique_ptr<TreeNode>(new TreeNode(value));
                    amount_of_nodes_++;
                } else {
                    recursiveInsert(node->right, value);
                }
            } else {
                
                node->value_count++;
                amount_of_nodes_++;
            }

        }

        template<class T>
        void BinarySearchTree<T>::insert(T value) {
            recursiveInsert(root_, value);
        }

        template<class T>
        bool BinarySearchTree<T>::remove(T value) {
            return recursiveRemove(root_, root_, value);
        }

        // removes node with matching value
        template<class T>
        bool BinarySearchTree<T>::recursiveRemove(std::unique_ptr<TreeNode> &parent, std::unique_ptr<TreeNode> &node, T value) {

            if (!node) {
                return false;
            }

            int node_occurrences = node->value_count;

            if (node->value == value) {

                // if 2 children
                if (node->left && node->right) {
                    T successor_val = successor(node)->value;
                    recursiveRemove(root_, root_, successor_val);
                    node->value = successor_val; 
                    
                // if 1 child
                } else if (node->left || node->right) {
                    
                    // pointer to whichever child exists
                    std::unique_ptr<TreeNode> &child = node->left ? node->left : node->right;

                    if (node == root_) {
                        root_ = std::move(child);
                    } else if (value < parent->value) {
                        parent->left = std::move(child);
                    } else {
                        parent->right = std::move(child);
                    }

                    amount_of_nodes_ -= node_occurrences;
                
                // if no children (leaf node)
                } else {
                    if (node == root_) {
                        root_.reset(nullptr);
                    
                    } else if (value < parent->value) {
                        parent->left.reset(nullptr);
                    } else {
                        parent->right.reset(nullptr);
                    }

                    amount_of_nodes_ -= node_occurrences;
                }

                return true;

            } else if (value < node->value) {
                recursiveRemove(node, node->left, value);
            } else {
                
                recursiveRemove(node, node->right, value);
            }

            return false;
            
        }

        // return how many nodes there are in the bst
        template<class T>
        int BinarySearchTree<T>::nodeCount() {
            return amount_of_nodes_;
        }

        // traverse the tree in preorder fashion. Visit the node, then left, then right.
        template<class T>
        void BinarySearchTree<T>::preorderTraversal(std::unique_ptr<TreeNode> &node, std::function<void(T)> callback) {

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
        void BinarySearchTree<T>::inorderTraversal(std::unique_ptr<TreeNode> &node, std::function<void(T)> callback) {

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
        void BinarySearchTree<T>::postorderTraversal(std::unique_ptr<TreeNode> &node, std::function<void(T)> callback) {

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

    }

}



