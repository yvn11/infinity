/**Red Black Node
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#include <algorithm>
#include <queue>
#include "rbnode.h"

using namespace std;

bool is_leaf(Node* node) {
  return (!node || (!node->left && !node->right)) ? true : false;
}

bool is_black(Node* node) {
  if (!node)
    return true;
  return node->color & BLACK;
}

void set_black(Node* node) {
  if (node)
    node->color |= BLACK;
}

void set_red(Node* node) {
  if (node)
    node->color |= RED;
}

void swap_color(Node* a, Node* b) {
  if (a && b) {
    swap(a->color, b->color);
  }
}

void swap_key(Node* a, Node* b) {
  if (a && b) {
    swap(a->key, b->key);
  }
}

void swap_node(Node* a, Node* b) {
  swap_color(a, b);
  swap_key(a, b);
}

bool is_leftchild(Node* node) {
  if (node->parent) {
    return node == node->parent->left;
  }
  return false;
}

bool is_rightchild(Node* node) {
  if (node->parent) {
    return node == node->parent->right;
  }
  return false;
}

Node* leftmost(Node* root) {
  Node* p = root;
  while (p && p->left)
    p = p->left;
  return p;
}

Node* rightmost(Node* root) {
  Node* p = root;
  while (p && p->right)
    p = p->right;
  return p;
}

Node* grandparent(Node* node) {
  if (node && node->parent) {
    return node->parent->parent;
  }
  return nullptr;
}

Node* uncle(Node* node) {
  if (node && node->parent) {
    Node* g = grandparent(node);
    if (!g) return nullptr;
    return is_leftchild(node->parent) ? g->right : g->left;
  }
  return nullptr;
}

Node* sibling(Node* node) {
  if (node && node->parent) {
    return is_rightchild(node) ? node->parent->left : node->parent->right;
  }
  return nullptr;
}

void left_rotate(Node* node) {
  if (!node)
    return;

  if (node->parent) {
    node->parent->left = node->right;
    node->left = node;
    node->right = nullptr;
  } else {
    Node *p = node->right;
    node->right = p->left;
    p->left = node;
  }
}

void right_rotate(Node* node) {
  if (!node)
    return;

  if (node->parent) {
    node->parent->right = node->left;
    node->left->right = node;
    node->left = nullptr;
  } else {
    Node *p = node->left;
    node->left = p->right;
    p->right = node;
  }
}

ostream& operator<< (ostream &o, Node &node) {
    return o << "[" << node.key 
      << '|' << (is_black(&node) ? "b" : "r") 
      << '|' << (is_leftchild(&node) ? "l" : (is_rightchild(&node) ? "r" : "rt")) << "]";
}

void print_tree(ostream &o, Node* root) {
  if (!root)
    return;

  Node* node = nullptr;
  queue<Node*> q;
  q.push(root);

  while (!q.empty()) {
    int count = q.size();
    while (count--) {
      node = q.front();
      q.pop();
      o << *node << ',';
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
    o << endl;
  }
}
