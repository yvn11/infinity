#include <iostream>
#include <limits.h>
#include "tree_node.h"

using namespace std;

class Solution {
public:

    int do_sum(TreeNode* root, int& cur) {
        if (!root)
          return 0;

        int left = do_sum(root->left, cur);
        int right = do_sum(root->right, cur);
        int tmp = max(root->val, max(left, right) + root->val);
        int sum = left + right + root->val;
        cur = max(cur, max(tmp, sum));
        return tmp;
    }

    int maxPathSum(TreeNode* root) {
        if (!root)
            return 0;

        int ret = INT_MIN;
        do_sum(root, ret);
        return ret;
    }
};

int main() {
  Solution s;
  TreeNode *root = new TreeNode(9);

  root->left = new TreeNode(6);
  root->right = new TreeNode(-3);
  /*
  root->left->left = new TreeNode(4);
  root->left->left->left = new TreeNode(10);
  root->left->right = new TreeNode(5);
  */
  root->right->left = new TreeNode(-6);
  root->right->right = new TreeNode(2);
  root->right->right->left = new TreeNode(2);
  root->right->right->left->left = new TreeNode(-6);
  root->right->right->left->right = new TreeNode(-6);
  root->right->right->left->left->left = new TreeNode(-6);
  cout << s.maxPathSum(root) << endl;
  return 0;
}
 
