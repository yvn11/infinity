#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void print_inorder(TreeNode* root, std::ostream &o) {
  if (!root)
    return;

  print_inorder(root->left, o);
  o << root->val << ',';
  print_inorder(root->right, o);
}
