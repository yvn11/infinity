#include <iostream>
#include <vector>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder,
        int root_ind, int begin, int end) {
      if (begin > end || begin < 0 || end >= inorder.size())
        return nullptr;

      int val = postorder[root_ind];
      TreeNode* root = new TreeNode(val);
      int i = begin;

      while (i <= end) {
        if (inorder[i] == val)
          break;
        ++i;
      }

      // root_ind-(end-i+1)
      root->left = buildTree(inorder, postorder, root_ind+i-end-1, begin, i-1);
      root->right = buildTree(inorder, postorder, root_ind-1, i+1, end);

      return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
      return buildTree(inorder, postorder, postorder.size()-1, 0, inorder.size()-1);
    }
};


int main() {
  Solution s;
  vector<int> postorder = {9, 15, 7, 20, 3};
  vector<int> inorder = {9, 3, 15, 20, 7};
  TreeNode* root = s.buildTree(inorder, postorder);
  print_inorder(cout, root);
  return 0;
}
