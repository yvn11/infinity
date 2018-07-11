#include <iostream>
#include <vector>
#include <deque>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
      vector<vector<int>> ret;
      if (!root)
        return ret;
      
      deque<TreeNode*> q;
      q.push_front(root);
      TreeNode* p = nullptr;
      
      while(!q.empty()) {
        int count = q.size();
        vector<int> v;
        
        while (count--) {
          if (ret.size() % 2 != 0) {
            p = q.back();
            q.pop_back();
            if (p->right) q.push_front(p->right);
            if (p->left) q.push_front(p->left);
          } else {
            p = q.front();
            q.pop_front();
            if (p->left) q.push_back(p->left);
            if (p->right) q.push_back(p->right);
          }
          
          v.push_back(p->val);
        }
        ret.push_back(v);
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

  auto ret = s.zigzagLevelOrder(root);
  for (auto v : ret) {
    for (auto n : v)
      cout << n << ',';
    cout << endl;
  }

  return 0;
}
