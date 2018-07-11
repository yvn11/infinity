#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
  TreeNode* secondLargest(TreeNode* root) {
    if (!root)
      return nullptr;

    if (root->right) {
      if (root->right->right)
        return secondLargest(root->right);
      else
        return root;
    } else if (root->left) {
      return root->left;
    }
    return nullptr;
  }
};

int main() {
  Solution s;
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(0);
  root->right = new TreeNode(4);
  root->left->right = new TreeNode(2);
  root->left->right->left = new TreeNode(1);
  root->right->right = new TreeNode(5);
  TreeNode *p = s.secondLargest(root);
  if (p) cout << p->val << endl;
  else cout << 0 << endl;

  return 0;
}
