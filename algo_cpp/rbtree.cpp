/**Red Black Tree
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#include "rbtree.h"

using namespace std;


void RBTree::insert(int key) {
  if (!_root) {
    _root = new Node(key);
    set_black(_root);
    return;
  }

  Node* x = new Node(key);
  insert(_root, x);
  insert_rebalance(x);
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

void RBTree::insert_rebalance(Node* x) {
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

Node* RBTree::find(Node* root, int key) {
  if (!root || root->key == key)
    return root;

  if (key < root->key) {
    return find(root->left, key);
  }
  return find(root->right, key);
}

Node* RBTree::find(int key) {
  return find(_root, key);
}

void RBTree::remove(int key) {
  Node* node = find(key); 
  if (!node)
    return;

  remove(node);
  //remove_rebalance(u);
}

void RBTree::remove(Node* node) {
  if (is_leaf(node)) {
    if (is_leftchild(node))
      node->parent->left = nullptr;
    else if (is_rightchild(node))
      node->parent->right = nullptr;
    delete node;
    return;
  }

  Node* u = nullptr;

  if (node->left)
    u = rightmost(node->left);
  else
    u = leftmost(node->right);

  swap_node(node, u);
  remove(u);
}

void RBTree::remove_rebalance(Node* u) {
  if (!u)
    return;

  if (u == _root) {
    set_black(u);
    return;
  }
    
  while (is_black(u) && u != _root) {
    Node* s = sibling(u);
  
    if (is_black(s) && (!is_black(s->left) || !is_black(s->right))) {
      Node* r = !is_black(s->left) ? s->left : s->right;
      if (is_leftchild(s) && is_leftchild(r)) {
        right_rotate(s->parent);
        set_black(r);
      } else if (is_leftchild(s) && is_rightchild(r)) {
        left_rotate(s);
        right_rotate(r->parent);
        set_black(r);
      } else if (is_rightchild(s) && is_leftchild(r)) {
        right_rotate(s);
        left_rotate(r->parent);
        set_black(r);
      } else if (is_rightchild(s) && is_rightchild(r)) {
        left_rotate(s->parent);
        set_black(r);
      }
    } else if (is_black(s) && is_black(s->left) && is_black(s->right)) {
      set_red(s);
    } else if (!is_black(s)) {
      if (is_rightchild(s)) {
        Node* p = s->left;
        left_rotate(s->parent);
        swap_color(s, p);
      } else if (is_leftchild(s)) {
        Node* p = s->right;
        right_rotate(s->parent);
        swap_color(s, p);
      }
    }
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
  obj.remove(35);
  obj.print_tree();
  obj.remove(20);
  obj.print_tree();
  return 0;
}
