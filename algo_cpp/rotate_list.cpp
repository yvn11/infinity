#include <iostream>
#include "list_node.h"

using namespace std;


class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int n = 0;
        ListNode *p = head, *new_hd = NULL;
        
        while (p != NULL) {
            p = p->next;
            n++;
        }
        
        if (n < 2 || k == 0 || k % n == 0) {
            return head;
        }

        p = head;
        for (int i = 0; i < n - k % n - 1; ++i) {
            p = p->next;
        }

        new_hd = p->next;
        p->next = NULL;
        
        p = new_hd;
        while (p && p->next != NULL) {
            p = p->next;
        }
        
        p->next = head;
        return new_hd;
    }
};

int main() {
  Solution s;
  ListNode *head = new ListNode(1), *p;

  p = head;
  for (int i = 1; i < 2; ++i) {
    p->next = new ListNode(i+1);
    p = p->next;
  }

  p = head;
  while (p != NULL) {
    cout << p->val << ',';
    p = p->next;
  }
  cout << endl;

  head = s.rotateRight(head, 2);
  p = head;
  while (p != NULL) {
    cout << p->val << ',';
    p = p->next;
  }
  return 0;
}
