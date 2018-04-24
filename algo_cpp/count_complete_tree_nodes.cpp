#include <iostream>
#include "tree_node.h"
#include <math.h>

using namespace std;

class Solution {
public:
    int height(TreeNode* root) {
      return root ? 1 + height(root->left) : -1;
    }

    int countNodes(TreeNode* root) {
        int h = height(root);

        return h < 0 ? 0 : 
          height(root->right) == h-1 ? pow(2, h) + countNodes(root->right) :
                pow(2, h-1) + countNodes(root->left);
    }
};

int main() {
  Solution s;
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->left->left = new TreeNode(4);
  //root->left->right = new TreeNode(5);
  root->right = new TreeNode(3);
  /*
  root->left->left->left = new TreeNode(4);
  root->left->left->right = new TreeNode(4);
  root->left->right->left = new TreeNode(5);
  root->left->right->right = new TreeNode(5);
  root->right->left = new TreeNode(8);
  root->right->right = new TreeNode(7);
  */
  cout << s.countNodes(root) << endl;
  return 0;
}
