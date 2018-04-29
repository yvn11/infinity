/**Red Black Tree
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#include "rbtree.h"

using namespace std;

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

void left_rotate(Node* node) {
  if (!node)
    return;

  if (node->parent) {
    node->parent->left = node->right;
    node->left = node;
    node->right = nullptr;
  } else {
    node->right->left = node;
    node->right = nullptr;
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
    node->left->right = node;
    node->left = nullptr;
  }
}

void RBTree::insert(int key) {
  if (!_root) {
    _root = new Node(key);
    set_black(_root);
    return;
  }

  Node* x = new Node(key);
  insert(_root, x);
  rebalance(x);
}

Node* RBTree::insert(Node* root, Node* x) {
  if (!root) 
    return x;

  if (x->key < root->key) {
    root->left = insert(root->left, x);
    root->left->parent = root;
    return root;
  }
  root->right = insert(root->right, x);
  root->right->parent = root;
  return root;
}

void RBTree::rebalance(Node* x) {
  if (is_black(x->parent))
    return;

  if (!is_black(uncle(x))) {
    while (x && x != _root && !is_black(x->parent)) {
      set_black(x->parent);
      set_black(uncle(x));
      set_red(grandparent(x));
      x = grandparent(x);
    }
  } else {
    if (is_leftchild(x) && is_leftchild(x->parent)) {
      Node *g = grandparent(x), *p = x->parent;
      right_rotate(g);
      swap_color(p, g);
    } else if (is_leftchild(x) && is_rightchild(x->parent)) {
      Node *g = grandparent(x), *p = x->parent;
      right_rotate(p);
      left_rotate(g);
      swap_color(x, g);
    } else if (is_rightchild(x) && is_leftchild(x->parent)) {
      Node *g = grandparent(x), *p = x->parent;
      left_rotate(p);
      right_rotate(g);
      swap_color(x, g);
    } else if (is_rightchild(x) && is_rightchild(x->parent)) {
      Node *g = grandparent(x), *p = x->parent;
      left_rotate(g);
      swap_color(p, g);
    }
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

int main() {
  RBTree obj;
  obj.insert(20);
  obj.insert(10);
  obj.insert(30);
  obj.insert(35);
  obj.insert(7);
  obj.print_tree();
  return 0;
}
