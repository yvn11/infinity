#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    int height(TreeNode* root) {
      if (!root)
        return 0;

      int left = height(root->left);
      if (left == -1)
        return -1;

      int right = height(root->right);
      if (right == -1)
        return -1;

      return abs(left-right) > 1 ? -1 : 1 + max(left, right);
    }

    bool isBalanced(TreeNode* root) {
      if (!root)
        return true;
      
      return height(root) != -1;
    }
};


int main() {
  Solution s;

  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(9);
  root->right = new TreeNode(4);
  root->left->right = new TreeNode(2);
  root->left->right->left = new TreeNode(1);
  root->left->right->left->right = new TreeNode(7);
  cout << s.isBalanced(root) << endl;
  return 0;
}
