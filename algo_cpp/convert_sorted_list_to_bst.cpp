#include <iostream>
#include "list_node.h"
#include "tree_node.h"

using namespace std;

void print_inorder(TreeNode* root);

class Solution {
public:
    TreeNode* convert(ListNode* begin, ListNode* end) {
        if (!begin || begin == end)
            return NULL;

        if (begin->next == end)
          return new TreeNode(begin->val);

        ListNode *p = begin, *q = begin;
     //   while (q != end && (!q->next || !q->next->next)) {
        while (q != end && q->next != end) {
            p = p->next;
            q = q->next->next;
        }

        TreeNode* root = new TreeNode(p->val);
        root->left = convert(begin, p);
        root->right = convert(p->next, end);
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
      return convert(head, NULL);
    }
};

void print_inorder(TreeNode* root) {
  if (!root)
    return;

  print_inorder(root->left);
  cout << root->val << ',';
  print_inorder(root->right);
}

void delete_list(ListNode* head) {
  if (!head)
    return;
  delete_list(head->next);
  head->next = NULL;
  delete(head);
  head = NULL;
}

void delete_tree(TreeNode* root) {
  if (!root)
    return ;

  delete_tree(root->left);
  root->left = NULL;
  delete_tree(root->right);
  root->right = NULL;
  delete(root);
  root = NULL;
}

int main() {
  Solution s;
  ListNode *head = new ListNode(1);
  ListNode *p = head;
  
  for (int i = 2; i < 19; ++i) {
    p->next = new ListNode(i);
    p = p->next;
  }

  p = head;
  while (p) {
    cout << p->val << ',';
    p = p->next;
  }
  cout << endl;

  TreeNode* root = s.sortedListToBST(head);
  print_inorder(root);
  cout << endl;
  delete_list(head);
  delete_tree(root);

  head = new ListNode(-10);
  head->next = new ListNode(-3);
  head->next->next = new ListNode(0);
  head->next->next->next = new ListNode(5);
  head->next->next->next->next = new ListNode(9);

  root = s.sortedListToBST(head);
  print_inorder(root);
  cout << endl;
  delete_list(head);
  delete_tree(root);

  return 0;
}
