#include "activity_bst.h"
#include <iostream>
#include <cmath>
using namespace std;

//written by Serhan Yilmaz with the student number 00031275

string fill_with_zeros(int num_zeros, const string& input) {
    int zeros_to_add = num_zeros - input.length();
    if (zeros_to_add < 0) zeros_to_add = 0;
    return string(zeros_to_add, '0') + input;
}
string number_to_time(int number) {
    return fill_with_zeros(2, to_string(number / 100)) + ":" + fill_with_zeros(2,
        to_string(number % 100));
}

void add_activity(tree_node*& root, int time, const string& activity)
{
    string time_str = number_to_time(time);
    int hours = stoi(time_str.substr(0, 2)), minutes = stoi(time_str.substr(3, 2));

    if (hours > 23 || hours < 0 || minutes > 59 || minutes < 0)
    {
        cout << "ERROR! Could not add activity " << activity << " due to illegal time value" << endl;
    }
    else
    {
        //create a new node
        tree_node* newNode = new tree_node(time, activity);
        if (root == nullptr)
        {
            root = newNode;
            cout << "Added activity " << activity << " at " << time_str << endl;
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
                    cout << "Added activity " << activity << " at " << time_str << endl;
                    //cout << "parent activity: " << newNode->parent->activity << " parent time: " << newNode->parent->time << endl;
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
                    cout << "Added activity " << activity << " at " << time_str << endl;
                    //cout << "parent activity: " << newNode->parent->activity << " parent time: " << newNode->parent->time << endl;
                    return;
                }
            }
        }
    }
}

void closestTimeUtil(struct tree_node* root, int given_time, int& min_diff, int& min_diff_key)
{
    //if there is no root, then just stop the function
    if (root == nullptr)
        return;

    if (abs((root->time - given_time < min_diff) && (root->time != given_time)))
    {
        min_diff = abs(root->time - given_time);
        min_diff_key = root->time;
    }

    // if k is less than the given time then go left, otherwise go right
    if (given_time < root->time)
    {
        closestTimeUtil(root->left, given_time, min_diff, min_diff_key);
    }
    else
    {
        closestTimeUtil(root->right, given_time, min_diff, min_diff_key);
    }
}

int closestTime(tree_node* root, int given_time)
{
    // Initialize minimum difference
    int min_diff = 2400, min_diff_time = -1;

    closestTimeUtil(root, given_time, min_diff, min_diff_time);
    return min_diff_time;
}

bool checkIfInTree(struct tree_node* root, int time)
{
    if (root == nullptr)
        return false;

    if (root->time == time)
        return true;

    /* then recur on left subtree */
    bool res1 = checkIfInTree(root->left, time);
    // node found, no need to look further
    if (res1) return true;

    /* node is not found in left,
    so recur on right subtree */
    bool res2 = checkIfInTree(root->right, time);

    return res2;
}

void print_activity_util(tree_node* root, int time)
{
    string time_str = number_to_time(time);
    int hours = stoi(time_str.substr(0, 2)), minutes = stoi(time_str.substr(3, 2));

    if (hours > 23 || hours < 0 || minutes > 59 || minutes < 0)
    {
        cout << "ERROR! Could not print activity at specific time due to illegal time" << endl;
        return;
    }
    if (root)
    {
        if (root->time == time)
        {
            string time_str = number_to_time(time);
            cout << "Time: " << time_str << ", Activity: " << root->activity << endl;
            return;
        }
        print_activity_util(root->left, time);
        print_activity_util(root->right, time);
    }
}

void print_activity(tree_node* root, int time)
{
    //print the name of the activity occuring at time 'time'
    //using postorder traversal, the function checks every node and finds the specified time.
    int time_lowerlimit = closestTime(root, time);
    bool lower_limit_in_tree = checkIfInTree(root, time_lowerlimit);
    bool in_tree = checkIfInTree(root, time);
    if (in_tree == true)
    {
        print_activity_util(root, time);
    }
    else
    {
        if (lower_limit_in_tree == true)
        {
            print_activity_util(root, time_lowerlimit);
        }
        else
        {
            string time_str = number_to_time(time);
            cout << "Time: " << time_str << ", Activity: " << "free" << endl;
            return;
        }
    }
}

void print_activity_and_duration(tree_node* root, int time)
{
    //print the duration of the activity occurring at time 'time'
    if (root)
    {
        print_activity_and_duration(root->left, time);
        if (root->time == time)
        {
            int closest_time = closestTime(root, time);
            if (closest_time == -1)
            {
                closest_time = 0000;
                string time_str = number_to_time(time);
                string time_closest_str = number_to_time(closest_time);
                cout << "Time period : [" << time_str << " - " << time_closest_str << "] : " << root->activity << endl;
                return;
            }
            else if (time < closest_time)
            {
                string time_str = number_to_time(time);
                string time_closest_str = number_to_time(closest_time);
                cout << "Time period : [" << time_str << " - " << time_closest_str << "] : " << root->activity << endl;
            }
            else
            {
                string time_str = number_to_time(time);
                string time_closest_str = number_to_time(closest_time);
                cout << "Time period : [" << time_closest_str << " - " << time_str << "] : " << root->activity << endl;
            }
        }
        print_activity_and_duration(root->right, time);

    }
}

void print_single_activity(tree_node* root, const string& activity)
{
    //print the duration of every occurrence of activity 'activity'

    if (activity == "free")
    {
        int closest_time = closestTime(root, 0);
        string time_str = number_to_time(0), time_str_next = number_to_time(closest_time);
        cout << "Time period: [" << time_str << " - " << time_str_next << "]: " << activity << endl;
        return;
    }

    if (root)
    {
        print_single_activity(root->left, activity);

        if (root->activity == activity)
        {
            int time = root->time;
            int closest_time = closestTime(root, time);

            if (closest_time == -1)
            {
                closest_time = 0000;
                string time_str = number_to_time(time);
                string time_str_next = number_to_time(closest_time);
                cout << "Time period: [" << time_str << " - " << time_str_next << "]: " << activity << endl;
                return;
            }

            string time_str = number_to_time(time);
            string time_str_next = number_to_time(closest_time);

            if (closest_time < time)
            {
                cout << "Time period: [" << time_str_next << " - " << time_str << "]: " << activity << endl;
            }
            else
            {
                cout << "Time period: [" << time_str << " - " << time_str_next << "]: " << activity << endl;
            }


        }
        print_single_activity(root->right, activity);
    }
}

void print_all_activities(tree_node* root)
{
    //print the starting time of every activity
    //using inorder traversal, as is starts with the earliest activity and ends with the latest activity.
    if (root)
    {
        print_all_activities(root->left);
        string time_str = number_to_time(root->time);
        cout << "[" << time_str << "]" << " - " << root->activity << endl;
        print_all_activities(root->right);
    }
}

void delete_tree(tree_node* root)
{
    //delete the tree pointed at by 'root'
    if (root == nullptr)
    {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}