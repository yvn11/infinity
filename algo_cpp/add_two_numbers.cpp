#include <iostream>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *ret=NULL, *p=NULL;
        int s=0, r=0;
        bool with_r = false;
        
        while (l1 != NULL || l2 != NULL) {
            s = 0;
            if (l1) s += l1->val;
            if (l2) s += l2->val;

            if (with_r) {
                s += r;
            }

            if (s >= 10) {
                r = s/10;
                s %= 10;
                with_r = true;
            } else {
                with_r = false;
                r = 0;
            }
            
            if (ret == NULL) {
                ret = new ListNode(s);
                p = ret;
            } else {    
                p->next = new ListNode(s);
                p = p->next;
            }
            
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        
        if (with_r) {
            p->next = new ListNode(r);
        }
        return ret;
    }
};


int main() {
  Solution s;
  ListNode *num1 = new ListNode(1), *p;
  ListNode *num2 = new ListNode(6);

  p = num1;
  for (int i = 1; i < 3; ++i) {
    p->next = new ListNode(i+1);
    p = p->next;
  }

  p = num2;
  for (int i = 8; i < 11; ++i) {
    p->next = new ListNode(i+1);
    p = p->next;
  }

  ListNode *head = s.addTwoNumbers(num1, num2);
  p = head;
  while (p != NULL) {
    cout << p->val << ',';
    p = p->next;
  }
  return 0;
}
