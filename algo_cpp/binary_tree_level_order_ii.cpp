#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
      vector<vector<int>> ret;
      
      if (!root)
        return ret;
      
      stack<vector<int>> s;
      queue<TreeNode*> q;
      q.push(root);
      TreeNode* p = nullptr;
      
      while (!q.empty()) {
        int count = q.size();
        vector<int> v;
        while (count--) {
          p = q.front();
          q.pop();
          if (p->left)
            q.push(p->left);
          if (p->right)
            q.push(p->right);
          v.push_back(p->val);
        }
        s.push(v);
      }
      
      while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
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

  auto ret = s.levelOrderBottom(root);
  for_each(ret.begin(), ret.end(), [](auto v) {
    for_each(v.begin(), v.end(), [](auto n) {
        cout << n << ',';
        });
    cout << endl;
    });

  return 0;
}
  
