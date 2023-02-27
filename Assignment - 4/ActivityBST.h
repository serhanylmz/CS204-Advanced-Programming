//
// Written by Serhan Yilmaz
// Student number: 00031275
//

#ifndef ACTIVITYBST_H
#define ACTIVITYBST_H
#include <iostream>
#include <string>
#include <ostream>

using namespace std;

struct tree_node {
    int time;
    string activity;
    tree_node *right;
    tree_node *left;
    tree_node *parent;
    tree_node(int t, const string &a) : time(t), activity(a),
                                        right(nullptr), left(nullptr),
                                        parent(nullptr) {}
};

class ActivityBST{
    friend ostream& operator<<(ostream& os, const ActivityBST& rhs);
    friend void recursiveAdder(ActivityBST &toAdd, tree_node *root);
    friend tree_node* createClone(tree_node* root); //copy constructor helper function, creates the copy of the tree given, then returns the head node, to be assigned in the copy constructor.
    friend ActivityBST operator+(const ActivityBST &lhs ,const ActivityBST& rhs);
private:
    tree_node *root; //the root of the Binary Search Tree
public:
    ActivityBST(); //default constructor
    ActivityBST(const ActivityBST& existing_tree); //copy constructor
    //tree_node* createClone(tree_node* node) const; //copy constructor helper function, creates the copy of the tree given, then returns the head node, to be assigned in the copy constructor.
    void deletor(tree_node* node);
    ~ActivityBST(); //destructor
    void add(int time, const string& activity); //takes an integer representing the time, and the name of the activity, then adds it to the tree. remember that this does not print anything.
    ActivityBST& operator=(const ActivityBST& rhs);
    ActivityBST& operator+=(const ActivityBST& rhs);
    void printTree(tree_node* node, ostream& os) const;

};



#endif //ACTIVITYBST_H
