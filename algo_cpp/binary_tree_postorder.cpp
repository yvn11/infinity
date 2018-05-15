#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    void push_left(TreeNode *p, stack<TreeNode*> &s) {
      if (!p)
        return;

      while (p) {
        if (p->right)
          s.push(p->right);
        s.push(p);
        p = p->left;
      }
    }
    
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (!root)
            return ret;
        
        TreeNode* p = root, *q = NULL;
        stack<TreeNode*> s;
        push_left(p, s);

        while (!s.empty()) {
          p = s.top();
          s.pop();

          if (p->right && !s.empty() && s.top() == p->right) {
            s.pop();
            s.push(p);
            p = p->right;
          } else {
            ret.push_back(p->val);
            p = NULL;
          }

          push_left(p, s);
        }
        return ret;
    }
};

int main() {
  Solution s;
  
  TreeNode *root = new TreeNode(1);
  root->right = new TreeNode(2);
  root->right->left = new TreeNode(3);
//  root->right->left = new TreeNode(3);
  /*
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
  root->left->left->left = new TreeNode(10);
  root->right->left->left = new TreeNode(8);
  root->right->left->left->right = new TreeNode(9);
*/
  for (auto n : s.postorderTraversal(root)) {
    cout << n << ',';
  }
  return 0;
}
