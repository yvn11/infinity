#include <iostream>
#include "list_node.h"

using namespace std;


class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
      if (!head)
        return head;
      
      ListNode* p = head, *q = head, *t = nullptr;
      n -= m;
      ListNode *pre_tail = nullptr, *new_tail = nullptr;
      
      while (--m > 0 && p) {
        pre_tail = p;
        p = p->next;
      }
      
      if (!p)
        return nullptr;
      
      if (!pre_tail)
        new_tail = head;

      q = p->next;
      while (n-- > 0 && q) {
        t = q->next;
        q->next = p;
        p = q;
        q = t;
      }

      if (!new_tail) {
        pre_tail->next->next = q;
        pre_tail->next = p;
        return head;
      }

      new_tail->next = q;
      return p;
    }
};


int main() {
  Solution s;

  ListNode* head = new ListNode(4);
  head->next = new ListNode(2);
  head->next->next = new ListNode(7);
  head->next->next->next = new ListNode(1);
  head->next->next->next->next = new ListNode(3);
  head->next->next->next->next->next = new ListNode(5);

  print_list(cout, head);
  head = s.reverseBetween(head, 1, 6);
  print_list(cout, head);

  return 0;
}
