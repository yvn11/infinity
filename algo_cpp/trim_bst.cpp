#include <iostream>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
      if (!root)
        return root;

      if (root->val < L) {
        return trimBST(root->right, L, R);
      }
      if (root->val > R) {
        return trimBST(root->left, L, R);
      }
      
      root->left = trimBST(root->left, L, R);
      root->right = trimBST(root->right, L, R);
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

  root = s.trimBST(root, 1, 3);
  print_inorder(root, cout);
  return 0;
}
