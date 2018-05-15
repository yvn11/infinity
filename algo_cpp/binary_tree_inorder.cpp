#include <iostream>
#include <vector>
#include <stack>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    void push_left(TreeNode *p, stack<TreeNode*> &s) {
        if (!p)
          return;
        while (p->left) {
          s.push(p);
          p = p->left;
        }
        s.push(p);
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (!root)
            return ret;
        
        TreeNode* p = root;
        stack<TreeNode*> s;
        s.push(p);
        push_left(p->left, s);
        
        while (!s.empty()) {
          p = s.top();
          push_left(p->left, s);
            
          while (!s.empty()) {
            p = s.top();
            s.pop();
            ret.push_back(p->val);
            push_left(p->right, s);
          }
        }
        return ret;
    }
};

int main() {
  Solution s;
  
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->left->left = new TreeNode(10);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
  root->right->left->left = new TreeNode(8);
  root->right->left->left->right = new TreeNode(9);

  for (auto n : s.inorderTraversal(root)) {
    cout << n << ',';
  }
  return 0;
}
