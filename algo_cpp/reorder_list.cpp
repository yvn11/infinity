#include <iostream>
#include "list_node.h"

using namespace std;


class Solution {
public:
    
    void reorderList(ListNode* head) {
        if (!head)
          return;

        ListNode* mid = head, *p = head->next;
        
        while (p && p->next) {
            mid = mid->next;
            p = p->next->next;
        }

        if (!mid->next)
          return;

        p = mid->next;
        ListNode *t = p->next, *q = nullptr, *s = nullptr;
        
        while (t) {
            q = t->next;
            t->next = p;
            p = t; t = q;
        }
        
        mid->next->next = nullptr;
        q = head;
        
        while (p) {
            t = q->next;
            s = p->next;
            q->next = p;
            p->next = t;
            q = t; p = s;
        }
        
        if (q->next)
          q->next = nullptr;
    }
};

int main() {
  Solution s;
  ListNode *head = new ListNode(1), *p;

  p = head;
  for (int i = 2; i <= 9; ++i) {
    p->next = new ListNode(i);
    p = p->next;
  }

  print_list(cout, head);
  s.reorderList(head);
  print_list(cout, head);
  
  return 0;
}
