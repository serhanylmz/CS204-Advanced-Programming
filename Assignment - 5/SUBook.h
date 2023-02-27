//
// Written by Serhan Yilmaz.
// Student Number: 00031275
//

#ifndef SUBOOK_H
#define SUBOOK_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Post;
class Comment;

class User
{
private:
    string name;
    vector<Post*> posts;
    int num_comments;
public:
    User(const string &username);
    ~User(); //destructor
    Post& createPost(const string& content);
    vector<Post*> getPosts();
    int getNumComments();
    string getName();
    void decreaseNumCommentsByOne();
    void incrementNumCommentsByOne();
};

class Post
{
private:
    User *postUser;
    string postContent;
    vector<Comment*> comments;
public:
    Post(User &user, const string &content);
    ~Post(); //destructor -- deletes all comments
    void addComment(string content, User* commenter);
    vector <Comment*> getComments();
    User& getUser();
    string getContent();
};

class Comment
{
private:
    User *commentUser;
    Post *commentPost;
    string commentContent;
public:
    Comment(User& user, Post& post, string comment);
    ~Comment(); //destructor -- deletes all comments
    User& getUser(); // returns the user who made the comment
    string getContent(); //returns the text content of the comment
    Post& getPost(); //returns the post that the commment is on

};

#endif //SUBOOK_H
