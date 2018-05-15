#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
      if (!root)
          return 0;
      
      int ret = 0;
      if (root->left) {
        if (!root->left->left && !root->left->right) {
          ret += root->left->val;
        } else {
          ret += sumOfLeftLeaves(root->left);
        }
      }
      ret += sumOfLeftLeaves(root->right);
      return ret;
    }
};


int main() {
  Solution s;

  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(0);
  root->right = new TreeNode(4);
  root->left->right = new TreeNode(2);
  root->left->right->left = new TreeNode(1);

  cout << s.sumOfLeftLeaves(root);
  return 0;
}
