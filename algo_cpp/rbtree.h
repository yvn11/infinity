/**Red Black Tree
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include "rbnode.h"

using namespace std;


class RBTree {
  private:
    Node* _root;

  public:
    RBTree() : _root(nullptr) {}
    void insert(int key);
    Node* insert(Node *root, Node *x);
    void insert_rebalance(Node* x); 
    void remove(int key);
    void remove(Node* root);
    void remove_rebalance(Node* u); 
    Node* find(int key);
    Node* find(Node* root, int key);
    void print_tree() {::print_tree(cout, _root);}
};
