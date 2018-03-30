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

        return (root->val == INT_MIN ? !root->left : this->isValidBST(root->left, mi, root->val-1))
          && (root->val == INT_MAX ? !root->right : this->isValidBST(root->right, root->val+1, ma));
    }
    
    bool isValidBST(TreeNode* root) {
      return this->isValidBST(root, INT_MIN, INT_MAX);
    }
};

int main() {
  Solution s;
  TreeNode *root = new TreeNode(INT_MIN), *p;
  
  root->left = new TreeNode(INT_MIN);
  //root->right = new TreeNode(18);
  //root->right->left = new TreeNode(7);
  //root->right->right = new TreeNode(20);
  cout << s.isValidBST(root) << endl;
  return 0;
}
 
