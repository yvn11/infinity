#include <iostream>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
      if (!head)
          return head;
      
      ListNode *q = head, *p = q->next, *t = nullptr;
      
      while (p) {
        t = p->next;
        p->next = q;
        q = p;
        p = t;
      }
      
      head->next = nullptr;
      return q;
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

  head = s.reverseList(head);
  print_list(cout, head);
  return 0;
}
