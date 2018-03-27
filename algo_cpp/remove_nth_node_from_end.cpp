#include <iostream>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *t = head, *del = head;
        int len = 0;

        while (t != NULL) {
            len++;
            t = t->next;
        }

        if (len == 1 && n == 1) {
            head = NULL;
            return head;
        }

        if (len == 2) {
            if (n == 1) {
                head->next = NULL;
            }else {
                head = head->next;
            }
            return head;
        }

        int target = len-n;
        
        if (target == 0) {
          head = head->next;
          return head;
        }
        del = head;
        int i = 0;

        while (i < target-1) {
            del = del->next;
            i++;
        }

        t = del->next;
        del->next = del->next->next;
        t = NULL;


        return head;
    }
};

int main() {
  Solution s;
  ListNode *head = new ListNode(1), *p;

  p = head;
  for (int i = 1; i < 3; ++i) {
    p->next = new ListNode(i+1);
    p = p->next;
  }

  p = head;
  while (p != NULL) {
    cout << p->val << ',';
    p = p->next;
  }
  cout << endl;

  head = s.removeNthFromEnd(head, 3);
  p = head;
  while (p != NULL) {
    cout << p->val;
    p = p->next;
  }

  return 0;
}
