#include <iostream>
#include <stack>
#include "tree_node.h"

using namespace std;

class BSTIterator {
private:
    stack<TreeNode*> s;

    void push_left(TreeNode* root) {
        if (!root)
          return;

        TreeNode* p = root;
        while (p->left) {
            s.push(p);
            p = p->left;
        }
        s.push(p);
    }

public:
    BSTIterator(TreeNode *root) {
      this->push_left(root);
    }

    bool hasNext() {
        return !this->s.empty();
    }

    int next() {
        TreeNode *q = this->s.top();
        this->s.pop();
        this->push_left(q->right);
        return q->val;
    }
};

int main() {
  TreeNode *root = new TreeNode(4);
  root->right = new TreeNode(6);
  root->left = new TreeNode(2);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(5);
  root->right->right = new TreeNode(7);

  BSTIterator it(root);

  while (it.hasNext())
      cout << it.next() << ',';
  cout << endl;

  return 0;
}
