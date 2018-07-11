#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
          return 0;
  
        int ret_l = this->minDepth(root->left);
        int ret_r = this->minDepth(root->right);
        if (ret_l == 0 || ret_r == 0)
            return 1 + max(ret_l, ret_r);
        else
            return 1 + min(ret_l, ret_r);
    }
};

int main() {
  Solution s;
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->left->left = new TreeNode(10);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
  root->right->left->left = new TreeNode(8);
  root->right->left->left->right = new TreeNode(9);
  cout << s.minDepth(root) << endl;
  return 0;
}

