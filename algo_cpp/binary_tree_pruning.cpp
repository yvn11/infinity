#include <iostream>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    
    TreeNode* pruneTree(TreeNode* root) {
        if (!root)
            return root;
        
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);

        if (root->val == 0 && !root->left && !root->right) {
          delete root;
          return NULL;
        }
        return root;
    }
};

void print_inorder(TreeNode* root) {
  if (!root)
    return;

  print_inorder(root->left);
  cout << root->val << ',';
  print_inorder(root->right);
}

int main() {
  Solution s;

  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(0);
  root->left->right = new TreeNode(1);
  root->right = new TreeNode(0);
  root->right->left = new TreeNode(1);
  root->right->right = new TreeNode(0);
  root = s.pruneTree(root);

  print_inorder(root);

  return 0;
}
