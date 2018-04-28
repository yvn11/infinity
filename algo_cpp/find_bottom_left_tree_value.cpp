#include <iostream>
#include <queue>
#include "tree_node.h"

using namespace std;

class Solution {

public:
    int findBottomLeftValue(TreeNode* root) {
      if (!root)
        return 0;

      queue<TreeNode*> q;
      q.push(root);
      TreeNode *p = NULL;

      while (!q.empty()) {
        p = q.front();
        q.pop();
        if (p->right)
          q.push(p->right);
        if (p->left)
          q.push(p->left);
      }

      return p->val;
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

  cout << s.findBottomLeftValue(root) << endl;
  return 0;
}
