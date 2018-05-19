#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void print_inorder(std::ostream &o, TreeNode* root) {
  if (!root)
    return;

  print_inorder(o, root->left);
  o << root->val << ',';
  print_inorder(o, root->right);
}
