/**
 * @file avltree.h
 * Declaraction of the AVLTree class. You will probably need to modify this
 * file to add helper functions.
 */

#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <locale>
#include <iomanip>


/**
 * The AVLTree class represents a linked-memory AVL Tree.
 * @tparam K the type of key stored in the tree
 * @tparam V the type of value stored in the tree
 */

class AVLTree
{
  private:
    /**
     * Node represents a tree node; that is, an element in a AVLTree.
     * It stores a key, value, and pointers to its left and right children.
     */
    struct Node {
        double timestamp;
        std::string  url;
        Node* left;
        Node* right;
        int height;

        /**
         * Node constructor; sets children to point to `NULL`.
         * @param newKey The object to use as a key
         * @param newValue The templated data element that the constructed
         *  node will hold.
         */
        Node(double& new_timestamp, std::string & new_url)
            : timestamp(new_timestamp), url(new_url), left(NULL), right(NULL), height(0)
        {
        }

        
    };

  public:
    /**
     * Constructor to create an empty tree.
     */
    AVLTree();

    /**
     * Copy constructor.
     * @param other The tree to copy
     */
    AVLTree( AVLTree& other);

    /**
     * Destructor; frees all nodes associated with this tree.
     */
    ~AVLTree();

    /**
     * Assignment operator.
     * @param rhs The tree to copy
     * @return A reference to the current tree
     */
     AVLTree& operator=( AVLTree& rhs);

    /**
     * Frees all nodes associated with this tree and sets it to be empty.
     */
    void clear();

    /**
     * Inserts a key and value into the AVLTree.
     * @param key The key to insert
     * @param value The value associated with the key
     */
    void insert(double & timestamp,  std::string &url);

    /**
     * Removes a key from the AVLTree. The key is assumed to exist in the tree.
     * @param key The key to remove
     */
    void remove(double& timestamp);

    /**
     * Finds an element in the AVL tree.
     * @param key The element to search for
     * @return The value stored for that key
     */
    std::string find(double& timestamp) ;

    /**
     * Prints the function calls to a stream.
     * @param out The stream to print to (default is stdout)
     */
    void printFunctionOrder(std::ostream& out = std::cout);

    /**
     * Prints the AVLTree to a stream.
     * @param out The stream to print to (default is stdout)
     */
    void print(std::ostream& out = std::cout, bool order = true) ;

    /**
     * This function is used for grading.
     * @param newOut The stream to print to
     */
    void setOutput(std::ostream& newOut);

    /**
     * Gets the in-order traversal of an AVL tree's keys.
     */
    std::vector<double> getInorderTraversal() ;

    /**
     * Gets the pre-order traversal of an AVL tree's keys.
     */
    std::vector<double> getPreorderTraversal() ;

    

  private:
    /**
     * The root of the tree.
     */
    Node* root;

    /**
     * Private helper function for the public #insert function.
     * @param node The current node in the recursion
     * @param key The key to insert
     * @param value The value associated with the key
     */
    void insert(Node*& subtree, double& timestamp,  std::string& url);

    /**
     * Private helper function for the public #remove function.
     * @param node The current node in the recursion
     * @param key The key to remove
     */
    void remove(Node*& subtree, double& timestamp);

    /**
     * Finds a value (by key) in the AVL tree.
     * @param node The node to search from (current subroot)
     * @param key The key to search for
     * @return The value stored for that key
     */
    std::string find(Node* subtree, double& timestamp) ;

    /**
     * Rotate the tree right (there is an imbalance on the left side).
     * @param node The node to rotate
     */
    void rotateRight(Node*& subtree);

    /**
     * Rotates the tree left (there is an imbalance on the right side).
     * @param node The node to rotate
     */
    void rotateLeft(Node*& subtree);

    /**
     * A right-left rotation.
     * This function should simply call rotateRight and rotateLeft.
     * @param node The node to rotate
     */
    void rotateRightLeft(Node*& subtree);

    /**
     * A left-right rotation.
     * This function should simply call rotateLeft and rotateRight.
     * @param node The node to rotate
     */
    void rotateLeftRight(Node*& subtree);

    /**
     * Rebalance a node by performing rotations. You can assume that node->left
     * and node->right are both balanced. Even if no rotations are required,
     * you should update the node's height.
     * @param node The node to balance.
     */
    void rebalance(Node*& subtree);

    /**
     * Return the node->height if the node is not NULL. Otherwise return -1.
     * Note: this function does not calculate the **actual** height of a node.
     * @param node The node's height to check
     * @return The height of the node if it's non-`NULL` or -1 if it is `NULL`
     */
    int heightOrNeg1( Node* subtree) ;

    /**
     * Swap the keys and values of two nodes.
     * @param first The first node to swap
     * @param second The node to swap with
     */
    void swap(Node*& first, Node*& second);

    /**
     * Helper function for #operator= and AVLTree(const AVLTree &).
     * @param subRoot The current node in the recursion
     */
    Node* copy(Node* subRoot);

    /**
     * Private helper function for clear that clears beneath the parameter node.
     * @param subRoot The current node in the recursion
     */
    void clear(Node* subRoot);

    /**
     * Gets the in-order traversal of an AVL tree's keys.
     * @param subRoot The current node in the recursion
     */
    void getInorderTraversal( Node* subRoot, std::vector<double>& traversal);

    /**
     * Gets the pre-order traversal of an AVL tree's keys.
     * @param subRoot The current node in the recursion
     */
    void getPreorderTraversal( Node* subRoot, std::vector<double>& traversal);

    /** This variable is used for grading. */
    std::ostream* _out;

    /** This variable tests the order of function calls **/
    std::vector<std::string> functionCalls;

    
};

#include "avltree.cpp"
