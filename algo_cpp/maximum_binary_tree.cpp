#include <iostream>
#include <vector>
#include <algorithm>
#include "tree_node.h"

using namespace std;

class Solution {
public:
  TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    if (nums.empty())
      return 0;
    return maximumBinaryTree(nums, 0, nums.size()-1);
  }

  TreeNode* maximumBinaryTree(vector<int>& nums, int begin, int end) {
    if (end < begin)
      return nullptr;

    if (begin == end)
      return new TreeNode(nums[begin]);
    
    auto it = max_element(nums.begin()+begin, nums.begin()+1+end);
    int ma = begin + distance(nums.begin()+begin, it);
    TreeNode* root = new TreeNode(nums[ma]);
    root->left = maximumBinaryTree(nums, begin, ma-1);
    root->right = maximumBinaryTree(nums, ma+1, end);

    return root;
  }
};

int main() {
  Solution s;
  vector<int> v = {3,2,1,6,0,5};
  //{32,3,5,1,16,7,3,9,11,4};
  TreeNode* root = s.constructMaximumBinaryTree(v);
  print_inorder(root, cout);
  return 0;
}

