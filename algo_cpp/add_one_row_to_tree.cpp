#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
      if (!root)
        return root;
      
      if (d == 1) {
        TreeNode* p = root;
        root = new TreeNode(v);
        root->left = p;
        return root;
      }
      
      if (d == 2) {
        TreeNode* p = root->left;
        root->left = new TreeNode(v);
        root->left->left = p;
        p = root->right;
        root->right = new TreeNode(v);
        root->right->right = p;
        return root;
      }
            
      root->left = addOneRow(root->left, v, d-1);
      root->right = addOneRow(root->right, v, d-1);
      return root;
      
    }
};

int main() {
  Solution s;
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(0);
  root->right = new TreeNode(4);
  root->left->right = new TreeNode(2);
  root->left->right->left = new TreeNode(1);

  root = s.addOneRow(root, 10, 3);
  print_inorder(root, cout);
  return 0;
}
