//
// Written by Serhan Yilmaz.
// Student Number: 00031275
//
#include "SUBook.h"

//User class here
User::User(const string &username) {
    name = username;
    num_comments = 0;

}

User::~User() {
    for (int i = 0; i < posts.size(); i++)
    {
        posts[i]->~Post();
    }
}


Post &User::createPost(const string& content) {
    Post *newPost = new Post(*this, content);
    posts.push_back(newPost);
    return *newPost;
}

vector<Post *> User::getPosts() {
    return posts;
}

int User::getNumComments() {
    return num_comments;
}

string User::getName() {
    return name;
}

void User::decreaseNumCommentsByOne() {
    num_comments -=1;
}

void User::incrementNumCommentsByOne() {
    num_comments += 1;
}

//User class ends
//---------------------------------
//Post class here

Post::Post(User &user, const string &content) {

    postUser = &user;
    postContent = content;
}


Post::~Post() {
    for(int i = 0; i < comments.size(); i++)
    {
        comments[i]->~Comment();
    }
}

void Post::addComment(string content, User *commenter) {
    Comment *newComment = new Comment(*commenter, *this, content);
    this->comments.push_back(newComment);
}

vector<Comment *> Post::getComments() {
    return comments;
}

User &Post::getUser() {
    return *postUser;
}

string Post::getContent() {
    return postContent;
}

//Post class ends
//---------------------------------
//Comment class here

Comment::Comment(User &user, Post &post, string comment) {
    commentUser = &user;
    commentPost = &post;
    commentContent = comment;
    user.incrementNumCommentsByOne();
}

Comment::~Comment() {
    commentUser->decreaseNumCommentsByOne();
}


User& Comment::getUser() {
    return *commentUser;
}

string Comment::getContent() {
    return commentContent;
}

Post& Comment::getPost() {
    return *commentPost;
}

//Comment class ends
