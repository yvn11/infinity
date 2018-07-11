#include <iostream>
#include "tree_node.h"

using namespace std;

class Solution {
public:
  
    bool isSymmetric(TreeNode* p, TreeNode* q) {
      if (!p && !q)
        return true;
      
      if (q && p)
        if (p->val == q->val)
          return true;
      return false;
    }
  
    bool checkSymmetric(TreeNode* p, TreeNode* q) {
      if (!p && !q)
        return true;
      
      return q && p ? isSymmetric(p, q) && checkSymmetric(p->right, q->left) &&
        checkSymmetric(p->left, q->right) : false;
    }
  
    bool isSymmetric(TreeNode* root) {
      if (!root)
        return true;
      return checkSymmetric(root->left, root->right);
    }
};


int main() {
  Solution s;

  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(4);
  root->right = new TreeNode(4);
  root->left->right = new TreeNode(2);
  root->right->left = new TreeNode(2);

  cout << s.isSymmetric(root) << endl;
  return 0;
}
