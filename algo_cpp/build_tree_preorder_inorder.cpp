#include <iostream>
#include <vector>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder,
                     int root_ind,  int begin, int end) {
      if (end >= inorder.size() || begin < 0 || begin > end)
        return nullptr;

      int val = preorder[root_ind];
      TreeNode* root = new TreeNode(val);

      int i = begin;
      while (i <= end) {
        if (inorder[i] == val)
          break;
        ++i;
      }

      root->left = buildTree(preorder, inorder, root_ind+1, begin, i-1);
      root->right = buildTree(preorder, inorder, root_ind+i-begin+1, i+1, end);
      return root;
    }
  
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
      TreeNode* ret = nullptr;

      return buildTree(preorder, inorder, 0, 0, inorder.size()-1); 
    }
};

int main() {
  Solution s;
  vector<int> preorder = {3, 9, 20, 15, 7};
  vector<int> inorder = {9, 3, 15, 20, 7};
  TreeNode* root = s.buildTree(preorder, inorder);
  print_inorder(cout, root);
  return 0;
}
