#include <iostream>
#include <stack>
#include <vector>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    void push_left(TreeNode* root, stack<TreeNode*> &s) {
      if (!root)
        return;

      while (root->left) {
        s.emplace(root);
        root = root->left;
      }
      s.push(root);
    }

    vector<int> findMode(TreeNode* root) {
      vector<int> ret;
      if (!root)
        return ret;

      stack<TreeNode*> s;
      push_left(root, s);
      TreeNode* p = nullptr;
      int max_freq = 0, count = 0;
      int prev = 0;

      while (!s.empty()) {
        p = s.top();
        s.pop();
        if (count == 0 || prev == p->val) ++count;
        else count = 1;

        prev = p->val;

        if (max_freq <= count) {
          if (max_freq < count) {
            max_freq = count;
            ret.clear();
          }
          ret.emplace_back(p->val);
        }

        if (p->right) {
          push_left(p->right, s);
        }
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

  for (auto n : s.findMode(root))
    cout << n << ',';
  cout << endl;
  return 0;
}
