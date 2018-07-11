#include <iostream>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
      if (!head)
        return head;

      ListNode* p = head;

      while (head && head->val == val) {
        p = head;
        head = head->next;
        delete p;
      }

      p = head;
      while (p) {
        if (p->next && p->next->val == val) {
          ListNode* q = p->next;
          p->next = q->next;
          delete q;
        } else {
          p = p->next;
        }
      }
      return head;
    }
};

int main() {
  Solution s;
  ListNode *head = new ListNode(1), *p;

  p = head;
  for (int i = 1; i < 7; ++i) {
    p->next = new ListNode(i+1);
    p = p->next;
  }
  head->val = 7;

  print_list(cout, head);
  head = s.removeElements(head, 7);
  print_list(cout, head);
  return 0;
}
