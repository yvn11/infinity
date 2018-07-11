#include <iostream>
#include "list_node.h"

using namespace std;


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
      ListNode* ret = new ListNode(0), *p = ret;
      while (l1 && l2) {
        if (l1->val < l2->val) {
          p->next = l1;
          l1 = l1->next;
        } else {
          p->next = l2;
          l2 = l2->next;
        }
        p = p->next;
      }
      
      if (l1)
        p->next = l1;
      if (l2)
        p->next = l2;
        
      return ret->next;
    }
};

int main() {
  Solution s;
  ListNode* p = nullptr;

  ListNode* l1 = new ListNode(1);
  p = l1;
  for (int i = p->val; i < 10; p = p->next)
    p->next = new ListNode(++i);

  ListNode* l2 = new ListNode(15);
  p = l2;
  for (int i = p->val; i < 20; p = p->next)
    p->next = new ListNode(++i);

  ListNode* head = s.mergeTwoLists(l1, l2);
  print_list(cout, head);
  return 0;
}
