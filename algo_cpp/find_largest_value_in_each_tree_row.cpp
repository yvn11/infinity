#include <iostream>
#include <queue>
#include <vector>
#include "tree_node.h"

using namespace std;

class Solution {
  public:
    vector<int> largestValues(TreeNode* root) {
      vector<int> ret;
      if (!root)
        return ret;

      queue<TreeNode*> q;
      q.push(root);

      while (!q.empty()) {
        TreeNode *p = q.front();
        int count = q.size();
        int mval = p->val;

        while (count-- > 0) {
          p = q.front();
          q.pop();
          mval = max(mval, p->val);

          if (p->left) {
            q.push(p->left);
          }
          if (p->right) {
            q.push(p->right);
          }
        }
        ret.push_back(mval);
      }

      return ret;
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

  for (auto c : s.largestValues(root)) {
    cout << c << ',';
  }
  cout << endl;
  return 0;
}
