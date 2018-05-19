#include <iostream>
#include <limits.h>
#include <stack>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    void push_left(TreeNode* root, stack<TreeNode*> &s) {
      if (!root)
        return;
      while (root && root->left) {
        s.push(root);
        root = root->left;
      }
      s.push(root);
    }

    int getMinimumDifference(TreeNode* root) {
      if (!root)
        return 0;

      TreeNode *p = root, *q = nullptr;
      stack<TreeNode*> s;
      s.push(p);

      int ret = INT_MAX;

      while (!s.empty()) {
        p = s.top();
        push_left(p->left, s);

        while (!s.empty()) {
          p = s.top();
          s.pop();

          if (q)
            ret = min(ret, abs(q->val - p->val));
          q = p;

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

  cout << s.getMinimumDifference(root) << endl;
  print_inorder(cout, root);
  return 0;
}
