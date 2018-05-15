#include <iostream>
#include <stack>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    void swap(TreeNode* root) {
        if (!root)
            return;
        
        TreeNode* a = root->left;
        root->left = root->right;
        root->right = a;
    }
    
    TreeNode* to_tail(TreeNode* root) {
        if (!root)
            return root;
        
        if (!root->left) 
            return root->right;
        
        root->right->right = root->left;
        root->left = NULL;
        return root->right->right;
    }
    
    void flatten(TreeNode* root) {
        if (!root)
            return;
        
        TreeNode* p = root, *q = root;
        stack<TreeNode*> s;
        
        while (p) {
            if (!p->right && !p->left) {
                if (s.empty())
                  break;
                q = s.top();
                s.pop();
                p->right = q;
                p = q;
                continue;
            }

            if (!p->right) {
                this->swap(p);
                p = p->right;
                continue;
            }
            
            if (p->left) {
                swap(p);
                s.push(p->left);
                p->left = NULL;
                p = p->right;
                continue;
            }

            if (p->right) {
              p = p->right;
              continue;
            }
        }
    }
};


int main() {
  Solution s;
  TreeNode* root = new TreeNode(1);
//  root->left = new TreeNode(2);
  root->right = new TreeNode(5);
//  root->left->left = new TreeNode(3);
//  root->left->right = new TreeNode(4);
  root->right->left = new TreeNode(6);

  s.flatten(root);

  TreeNode* p = root;
  while (p) {
    cout << p->val << ',';
    p = p->right;
  }
  cout << endl;

  return 0;
}
