#include <iostream>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next)
            return head;
        
        ListNode *p = head, *q = head->next;
        ListNode *even = q;
        
        while (p->next && q->next) {
            p->next = q->next;
            p = p->next;
            q->next = p->next;
            q = q->next;
        }
        
        p->next = even;        
        return head;
    }
};


int main() {
  Solution s;
  ListNode *head = new ListNode(1);
  ListNode *p = head;

  for (int i = 2; i < 13; ++i, p = p->next) {
    p->next = new ListNode(i);
  }
  
  head = s.oddEvenList(head);
  p = head;

  while (p) {
    cout << p->val << ',';
    p = p->next;
  }
  cout << endl;

  return 0;
}
