#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    TreeNode* left_most(TreeNode *p) {
        while (p && p->left) {
           p = p->left;
        }
        return p;
    }
    
    void swap(TreeNode *a, TreeNode *b) {
        int t = a->val;
        a->val = b->val;
        b->val = t;
    }
    
    TreeNode* del_node(TreeNode *root, int key) {
        TreeNode *q = NULL;
        
        if (!root)
          return root;

        if (root->val < key) {
          root->right = del_node(root->right, key);
        } else if (root->val > key) {
          root->left = del_node(root->left, key);
        } else {
          if (!root->right) {
            q = root->left;
            delete root;
            return q;
          } else if (!root->left) {
            q = root->right;
            delete root;
            return q;
          } else {
            q = left_most(root->right);
            root->val = q->val;
            root->right = del_node(root->right, q->val);
          }
        }

        return root;
    }
    
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root)
          return root;
        
        root = del_node(root, key);
        return root;
    }
};


int main() {
  Solution s;
  int val = 33; 
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(0);
  root->right = new TreeNode(33);
  //root->left->left = new TreeNode(2);
  root->left->right = new TreeNode(1);
  root->right->left = new TreeNode(25);
  root->right->right = new TreeNode(40);
  root->right->left->left = new TreeNode(11);
  root->right->left->right = new TreeNode(31);
  root->right->right->left = new TreeNode(34);
  root->right->right->right = new TreeNode(45);
  root->right->right->left->right = new TreeNode(36);
  root->right->right->right->left = new TreeNode(43);
  root->right->right->right->right = new TreeNode(46);
  root->right->right->left->right->left = new TreeNode(35);
  root = s.deleteNode(root, val);
  print_inorder(root, cout);

  return 0;
}
