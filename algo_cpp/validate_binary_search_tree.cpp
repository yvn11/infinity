#include <iostream>
#include <limits.h>
#include "tree_node.h"

using namespace std;


class Solution {
public:
    bool isValidBST(TreeNode* root, int mi, int ma) {
        if (!root) {
            return true;
        }

        if (root->val < mi || root->val > ma) {
          return false;
        }
        return this->isValidBST(root->left, mi, root->val-1)
          && this->isValidBST(root->right, root->val+1, ma);
    }
    
    bool isValidBST(TreeNode* root) {
      return this->isValidBST(root, INT_MIN, INT_MAX);
    }
};

int main() {
  Solution s;
  TreeNode *root = new TreeNode(10), *p;
  
  root->left = new TreeNode(4);
  root->right = new TreeNode(18);
  root->right->left = new TreeNode(7);
  root->right->right = new TreeNode(20);
  cout << s.isValidBST(root) << endl;
  return 0;
}
 
