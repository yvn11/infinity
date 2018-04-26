#include <iostream>
#include <limits.h>
#include "list_node.h"

using namespace std;

class Solution {
public:
    
    ListNode* insertionSortList(ListNode* head) {
        if (!head)
            return NULL;

        ListNode* ret = new ListNode(INT_MIN), *p = ret, *c = head, *n = NULL;

        while (c) {
          n = c->next;

          while (p->next && p->next->val < c->val) {
            p = p->next;
          }

          c->next = p->next;
          p->next = c;
          p = ret;
          c = n;
        }

        return ret->next;
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

  head = s.insertionSortList(head);
  ListNode* p = head;
  while (p) {
    cout << p->val << ',';
    p = p->next;
  }
  cout << endl;
  return 0;
}
