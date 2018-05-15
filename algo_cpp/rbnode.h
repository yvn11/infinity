/**Red Black Node
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include <iostream>

#define RED 0
#define BLACK 1

using namespace std;

struct Node {
  int key;
  bool color;
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
bool is_leaf(Node* node);
void set_black(Node* node);
void set_red(Node* node);
void swap_color(Node* a, Node* b);
void swap_key(Node* a, Node* b);
void swap_node(Node* a, Node* b);
Node* uncle(Node* node);
Node* sibling(Node* node);
Node* grandparent(Node* node);
bool is_leftchild(Node* node);
bool is_rightchild(Node* node);
Node* leftmost(Node* root);
Node* rightmost(Node* root);
void left_rotate(Node* node);
void right_rotate(Node* node);
void print_tree(ostream &o, Node* root);
