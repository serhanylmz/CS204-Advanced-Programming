//
// Written by Serhan Yilmaz
// Student number: 00031275
//

#include "ActivityBST.h"

using namespace std;

inline string fill_with_zeros(int num_zeros, const string &input) {
    int zeros_to_add = num_zeros - input.length();
    if (zeros_to_add < 0) zeros_to_add = 0;
    return string(zeros_to_add, '0') + input;
}

inline string number_to_time(int number) {
    if (number > 2359 || number < 0) return "ERROR";
    return fill_with_zeros(2, to_string(number / 100)) + ":" +
           fill_with_zeros(2, to_string(number % 100));
}

ActivityBST::ActivityBST() {
    root = nullptr;
}

tree_node* createClone(tree_node* root) {
    if (root == nullptr){
        return nullptr;
    }
    tree_node* treeClone = new tree_node(root->time, root->activity);
    treeClone->left = createClone(root->left);
    treeClone->right = createClone(root->right);

    return treeClone;
}

ActivityBST::ActivityBST(const ActivityBST &existing_tree) {
    tree_node* funcRoot = existing_tree.root;
    root = createClone(funcRoot);
}

void ActivityBST::add(int time, const string& activity){
    if(time <= 2359 && time >= 0000)
    {
        //create a new node
        tree_node* newNode = new tree_node(time, activity);
        if (root == nullptr)
        {
            root = newNode;
            return;
        }
        //declare the current node and the parent node
        tree_node* curr = root;
        tree_node* parent = nullptr;

        while (true)
        {
            parent = curr;
            //if the time is smaller than the current time then go left otherwise go right
            if (time < curr->time)
            {
                curr = curr->left;
                if (curr == nullptr)
                {
                    parent->left = newNode;
                    newNode->parent = parent;
                    return;
                }
            }
            else
            {
                curr = curr->right;
                if (curr == nullptr)
                {
                    parent->right = newNode;
                    newNode->parent = parent;
                    return;
                }
            }
        }
    }

}


void ActivityBST::deletor(tree_node* node){
    if(node == nullptr){return;} // if the node is nullptr then there's nothing left on that side of the tree
    //so just return
    else {
        deletor(node->left); //check for the left side of the tree
        deletor(node->right); //check for the right side of the tree
        delete node; //when you reach the leaves, delete the leaves
        //and the recursive call continues until the initial node = nullptr
        //and when the initial node is nullptr, it means that the tree is fully deleted.
    }

}

ActivityBST::~ActivityBST(){
    tree_node* funcRoot = this->root; //get the current root with 'this'
    deletor(funcRoot); //call the deletor function with the current root.
}

ActivityBST& ActivityBST::operator=(const ActivityBST &rhs){
    if (this == &rhs){return *this;} // why would we want to put extra load on the cpu? just don't do anything if the lhs and rhs are the same
    deletor(this->root); //if not, first delete 'this' and free the memory
    ActivityBST lhs; //create a lhs from scratch, now lhs will have root = nullptr
    lhs.root = createClone(rhs.root); //first clone the tree in the rhs, and then assign the root
    this->root = lhs.root; //now assign the new root to 'this'
    return *this; //finally return '*this'
}

void recursiveAdder(ActivityBST &toAdd, tree_node *root)
{
    if(root == nullptr){return;}
    recursiveAdder(toAdd, root->left);
    recursiveAdder(toAdd, root->right);
    toAdd.add(root->time, root->activity);
}


ActivityBST operator+(const ActivityBST &lhs, const ActivityBST &rhs){
    ActivityBST newTree;
    tree_node *rhsRoot = rhs.root, *lhsRoot = lhs.root;

    recursiveAdder(newTree, rhsRoot);
    recursiveAdder(newTree, lhsRoot);
    return newTree;
}

ActivityBST& ActivityBST::operator+=(const ActivityBST &rhs){
    tree_node* rhsRoot = rhs.root;
    recursiveAdder(*this, rhsRoot);
    return *this;
}

void ActivityBST:: printTree(tree_node *node, ostream &os) const {
    if (node == nullptr){return;}
    printTree(node->left, os);
    os << "[" << number_to_time(node->time) << "] - " << node->activity << endl;
    printTree(node->right, os);
}

 ostream& operator<<(ostream &os, const ActivityBST &rhs){
    rhs.printTree(rhs.root, os);
    return os;
}


