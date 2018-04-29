#include <iostream>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    void find_mistake(TreeNode* root, 
        TreeNode** prev, TreeNode** p, 
        TreeNode** q, TreeNode** last) {

      if (!root)
        return;

      this->find_mistake(root->left, prev, p, q, last);
      if ((*prev) && (*prev)->val > root->val) {
        if (!(*p)) {
          *p = *prev;    
          *q = root;
        } else {
          *last = root;
        }
      }
      *prev = root;
      this->find_mistake(root->right, prev, p, q, last);
    }

    void swap(TreeNode* p, TreeNode* q) {
      int t;
      t = q->val;
      q->val = p->val;
      p->val = t;
    }

    void recoverTree(TreeNode* root) {
        if (!root)
            return;
        
        TreeNode *p = nullptr, *q = nullptr, *prev = nullptr, *last = nullptr;
        this->find_mistake(root, &prev, &p, &q, &last);

        if (last && p) {
          cout << "last p" << endl;
          this->swap(last, p);
        }
        else if (q && last) {
          cout << "qp" << endl;
          this->swap(q, p);
        }
    }
};


int main() {
  Solution s;
  TreeNode *root = new TreeNode(1);
  root->right = new TreeNode(0);
  /*
  root->left = new TreeNode(1);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(2);
  root->right->right = new TreeNode(7);
*/
  s.recoverTree(root);

  print_inorder(root, cout);
  return 0;
}
