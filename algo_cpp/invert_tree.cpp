#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    
    TreeNode* invertTree(TreeNode* root) {
      if (!root)
        return root;

      TreeNode* t = root->left;
      root->left = root->right;
      root->right = t;

      root->left = invertTree(root->left);
      root->right = invertTree(root->right);

      return root;
    }
};


int main() {
  Solution s;
  TreeNode *root = new TreeNode(1);
  root->right = new TreeNode(0);
  root->left = new TreeNode(5);
  root->left->left = new TreeNode(9);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(2);
  root->right->right = new TreeNode(7);
  root->right->left->left = new TreeNode(4);
  root->right->right->right = new TreeNode(4);
  root->left->left->left = new TreeNode(8);
  root->left->right->right = new TreeNode(8);

  root = s.invertTree(root);
  print_inorder(root, cout);
  
  return 0;
}
