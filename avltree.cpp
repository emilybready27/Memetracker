
/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 
#include <queue>
#include "avltree.h"


using namespace std;
 
std::string AVLTree::find(double& timestamp) 
{
    return find(root, timestamp);
}
 
std::string AVLTree::find(Node* subtree, double& timestamp) 
{
    if (subtree == NULL)
        return "";
    else if (timestamp == subtree->timestamp)
        return subtree->url;
    else {
        if (timestamp < subtree->timestamp)
            return find(subtree->left, timestamp);
        else
            return find(subtree->right, timestamp);
    }
}
 
 
void AVLTree::rotateLeft(Node*& t)
{
    Node * replace_node = t->right;
    t->right = replace_node->left;
    replace_node->left = t;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = replace_node;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}
 
void AVLTree::rotateLeftRight(Node*& t)
{
 
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}
 
void AVLTree::rotateRight(Node*& t)
{
 
    // your code here
    Node * replace_node = t->left;
    t->left = replace_node->right;
    replace_node->right = t;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = replace_node;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}
 
void AVLTree::rotateRightLeft(Node*& t)
{
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}
 
void AVLTree::rebalance(Node*& subtree)
{
    if (subtree == NULL) {
        return;
    }
 
 
    if ((heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)) == -2) {
        if ((heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left)) < 0) { 
            rotateRight(subtree);
        }
        else {
            rotateLeftRight(subtree);
        }
    }
 
    if ((heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)) == 2) {
 
        if ((heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left)) > 0) { 
            rotateLeft(subtree);
        }
        else { 
            rotateRightLeft(subtree);
        }
    }
}
 
void AVLTree::insert(double & timestamp,  std::string & url)
{
    insert(root, timestamp , url);
}
 
void AVLTree::insert(Node*& subtree, double& timestamp,  std::string& url)
{
    cout << timestamp << endl;
    if (subtree == NULL) {
        subtree = new Node(timestamp, url);
    }
    else if (timestamp < subtree->timestamp) {
        insert(subtree->left, timestamp, url);
    }
    else if (timestamp > subtree->timestamp) {
        insert(subtree->right, timestamp, url);
    } else if (timestamp == subtree->timestamp) {
        subtree->url = url;
        return;
    }
    rebalance(subtree);
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}
 
void AVLTree::remove(double& timestamp)
{
    remove(root, timestamp);
}
 
void AVLTree::remove(Node*& subtree, double& timestamp)
{
    if (subtree == NULL)
        return;
 
    if (timestamp < subtree->timestamp) {
        // your code here
        remove(subtree->left,timestamp);
    } else if (timestamp > subtree->timestamp) {
        // your code here
        remove(subtree->right,timestamp);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            //delete current node;
            delete subtree;
            subtree=NULL;
        }else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //iop = rightmost node of left subtree.
            Node* temp = subtree->left;
            while (temp->right!=NULL)
            {
              temp = temp->right;
            }
            subtree->timestamp = temp->timestamp;
            subtree->url = temp->url;
            remove(subtree->left, temp->timestamp);
        } else {
 
            Node *temp;
            if(subtree->left!=NULL)
            {
                temp = subtree->left;
                *subtree = *temp;
                delete temp;
                temp = NULL;
 
            }
            else if(subtree->right!=NULL)
            {
                temp = subtree->right;
                *subtree = *temp;
                delete temp;
                temp = NULL;
 
            }
        }
    }
    rebalance(subtree);
}
 
 
AVLTree::AVLTree()
    : root(NULL), _out(&std::cout)
{
 
}
 
AVLTree::AVLTree( AVLTree& other)
    : root(copy(other.root)), _out(&std::cout)
{
 
}
 
AVLTree::~AVLTree()
{
    clear(root);
}
 
std::vector<double> AVLTree::getInorderTraversal() 
{
    std::vector<double> traversal;
    getInorderTraversal(root, traversal);
    return traversal;
}
 
void AVLTree::getInorderTraversal( Node* subRoot, std::vector<double>& traversal) 
{
    if (subRoot == NULL) {
        return;
    }
    getInorderTraversal(subRoot->left, traversal);
    traversal.push_back(subRoot->timestamp);
    getInorderTraversal(subRoot->right, traversal);
}
 
std::vector<double> AVLTree::getPreorderTraversal() 
{
    std::vector<double> traversal;
    getPreorderTraversal(root, traversal);
    return traversal;
}
 
void AVLTree::getPreorderTraversal( Node* subRoot, std::vector<double>& traversal) 
{
    if (subRoot == NULL) {
        return;
    }
    traversal.push_back(subRoot->timestamp);
    getPreorderTraversal(subRoot->left, traversal);
    getPreorderTraversal(subRoot->right, traversal);
}
 
 
 
AVLTree& AVLTree::operator=( AVLTree& rhs)
{
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}
 
void AVLTree::clear()
{
    clear(root);
    root = NULL;
}
 
typename AVLTree::Node* AVLTree::copy(Node* subRoot)
{
    if (subRoot == NULL)
        return NULL;
 
    // Copy this node and its children
    Node* newNode = new Node(subRoot->timestamp, subRoot->url);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}
 
void AVLTree::clear(Node* subRoot)
{
    if (subRoot == NULL)
        return;
 
    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}
 
void AVLTree::swap(Node*& first, Node*& second)
{
    double temptimestamp = first->timestamp;
    std::string tempurl = first->url;
    first->timestamp = second->timestamp;
    first->url = second->url;
    second->timestamp = temptimestamp;
    second->url = tempurl;
}
<<<<<<< HEAD

=======
 
>>>>>>> fdef20ac42233f6cd1adbbf2d605133b852787bd
int AVLTree::heightOrNeg1(Node* node)
{
    if (node == NULL)
        return -1;
    else
        return node->height;
}
<<<<<<< HEAD

=======
 
>>>>>>> fdef20ac42233f6cd1adbbf2d605133b852787bd
/*void AVLTree::print(std::ostream& out, bool order)
{
    if(order)
        printFunctionOrder(out);
    printTree(AVLTreeNodeDescriptor<Node>(root), out);
}*/
<<<<<<< HEAD

=======
 
>>>>>>> fdef20ac42233f6cd1adbbf2d605133b852787bd
// class for generic printing
 
/*template <typename Node>
class AVLTreeNodeDescriptor
    : public GenericNodeDescriptor<AVLTreeNodeDescriptor<Node>>
{
  public:
    AVLTreeNodeDescriptor(const Node* root) : subRoot(root)
    {
    }
    bool isNull() const
    {
        return subRoot == NULL;
    }
 
    std::string key() const
    {
        std::stringstream ss;
        ss << subRoot->key;
        return ss.str();
    }
 
    AVLTreeNodeDescriptor left() const
    {
        return AVLTreeNodeDescriptor(subRoot->left);
    }
    AVLTreeNodeDescriptor right() const
    {
        return AVLTreeNodeDescriptor(subRoot->right);
    }
 
  private:
    const Node* subRoot;
};
 
template <class K, class V>
void AVLTree<K, V>::printFunctionOrder(std::ostream& out) const
{
    for (int i = 0; i < (int)functionCalls.size(); i++) {
        out << functionCalls[i] << std::endl;
    }
}
<<<<<<< HEAD

=======
 
>>>>>>> fdef20ac42233f6cd1adbbf2d605133b852787bd
/*template <class K, class V>
void AVLTree<K, V>::setOutput(std::ostream& newOut)
{
    _out = &newOut;
}
*/