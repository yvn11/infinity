#include <iostream>
#include <queue>
#include <math.h>
#include "tree_node.h"

using namespace std;

class Solution {
  public:
    int widthOfBinaryTree(TreeNode* root) {
      if (!root)
        return 0;

      queue<pair<TreeNode*, int>> ranks;
      ranks.push(make_pair(root, 1));
      int ret = 0;

      while (!ranks.empty()) {
        int count = ranks.size();
        auto &begin = ranks.front();

        while (count--) {
          auto &p = ranks.front();
          ranks.pop();
          ret = max(ret, (p.second)-(begin.second)+1);

          if ((p.first)->left)
            ranks.push(make_pair((p.first)->left, 2*p.second));

          if ((p.first)->right)
            ranks.push(make_pair((p.first)->right, 2*p.second+1));
        }
      }

      return ret;
    }
};


int main() {
  Solution s;

  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(3);
  root->right = new TreeNode(2);
  root->left->left = new TreeNode(5);
  root->left->right = new TreeNode(3);
  root->right->right = new TreeNode(9);

  cout << s.widthOfBinaryTree(root) << endl;
  return 0;
}
