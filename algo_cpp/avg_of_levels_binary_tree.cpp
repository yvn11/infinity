#include <iostream>
#include <queue>
#include <vector>
#include "tree_node.h"

using namespace std;


class Solution {
public:
  vector<double> averageOfLevels(TreeNode* root) {
    vector<double> ret;
    if (!root)
      return ret;

    TreeNode *p = NULL;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
      p = q.front();
      int count = q.size();
      double sum = 0.0, n = count;

      while (count--) {
        p = q.front();
        q.pop();
        if (p->left) {
          q.push(p->left);
        }
        if (p->right) {
          q.push(p->right);
        }
        sum += p->val;
      }
      ret.push_back(sum/n);
    }
    return ret;
  }
};

int main() {
  Solution s;
  
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
  root->right->right->left = new TreeNode(8);
  root->right->right->right = new TreeNode(9);

  for (auto d : s.averageOfLevels(root)) {
  cout << d << ',';
  }
  cout << endl;

  return 0;
}
