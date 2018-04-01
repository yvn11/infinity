#include <iostream>
#include <queue>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
      vector<vector<int>> ret;
      if (!root)
        return ret;

      TreeNode* p = root;
      queue<TreeNode*> q;
      int count = 0;
      q.push(root);

      while (!q.empty()) {
        p = q.front();
        count = q.size();
        vector<int> v;
        while (!q.empty() && count-- > 0) {
          p = q.front();
          if (p->left)
            q.push(p->left);
          if (p->right)
            q.push(p->right);
          v.push_back(p->val);
          q.pop();
        }
        ret.push_back(v);
      }

      return ret;
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
  
  for (auto v : s.levelOrder(root))
    for (auto n : v)
      cout << n << ',';
  cout << endl;
  return 0;
}

