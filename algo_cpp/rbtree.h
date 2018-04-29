/**Red Black Tree
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

#define RED 0
#define BLACK 1

struct Node {
  int key;
  int color;
  Node* left;
  Node* right;
  Node* parent;

  Node(int key) : key(key), color(RED), 
    left(nullptr), right(nullptr), parent(nullptr) 
  {}

  bool operator< (Node &b) {
    return key < b.key;
  }

};

ostream& operator<< (ostream &o, Node &node);

bool is_black(Node* node);
void set_black(Node* node);
void set_red(Node* node);
void swap_color(Node* a, Node* b);
Node* uncle(Node* node);
Node* grandparent(Node* node);
bool is_leftchild(Node* node);
bool is_rightchild(Node* node);
void left_rotate(Node* node);
void right_rotate(Node* node);
void print_tree(ostream &o, Node* root);


class RBTree {
  private:
    Node* _root;

  public:
    RBTree() : _root(nullptr) {}
    void insert(int key);
    Node* insert(Node *root, Node *x);
    void rebalance(Node* x); 
    void remove(int key);
    void find(int key);
    void print_tree() {::print_tree(cout, _root);}
};
