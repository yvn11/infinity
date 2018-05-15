#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
      if (!p && !q)
        return true;
      
      if (!p || !q || p->val != q->val)
        return false;
      
      return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right)); 
    }
};

int main() {
  Solution s;

  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(0);
  root->right = new TreeNode(4);
  root->left->right = new TreeNode(2);
  root->left->right->left = new TreeNode(1);

  TreeNode *other = new TreeNode(3);
  other->left = new TreeNode(0);
  other->right = new TreeNode(4);
  other->left->right = new TreeNode(2);
  other->left->right->left = new TreeNode(1);
  cout << s.isSameTree(root, other) << endl;
  return 0;
}
