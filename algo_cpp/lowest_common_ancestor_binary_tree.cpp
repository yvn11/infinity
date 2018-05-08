#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
      if (!root || p == root || q == root)
        return root;
      
      TreeNode *left = lowestCommonAncestor(root->left, p, q);
      TreeNode *right = lowestCommonAncestor(root->right, p, q);
      
      return (left && right) ? root : (!left ? right : left);
    }
};


int main() {
  Solution s;
  
  TreeNode *root = new TreeNode(3);
  TreeNode* y = root->left = new TreeNode(9);
  root->right = new TreeNode(4);
  TreeNode* x = root->left->right = new TreeNode(2);
  root->left->right->left = new TreeNode(1);

  TreeNode* p = s.lowestCommonAncestor(root, x, y);
  cout << (p ? p->val : -1) << endl;
  return 0;
}
