#include <iostream>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode* hash(ListNode *head) {
      if (!head || !(head->next))
        return nullptr;

      unordered_set<ListNode*> mem;
      ListNode *p = head;
      while (p) {
        if (mem.find(p->next) != mem.end())
          return p->next;
        mem.insert(p);
        p = p->next;
    }

    ListNode* detectCycle(ListNode *head) {
      if (!head || !(head->next))
        return nullptr;

      ListNode *ret = nullptr;
      ListNode *p = head, *q = head;

      while (q && p) {
        p = p->next;
        if (!q->next)
          return nullptr;
        q = q->next->next;
        if (p == q) {
          ret = p;
          break;
        }
      }

      if (!ret)
        return ret;

      p = head;
      while (p && q) {
        if (p == q) {
          ret = p;
          break;
        }

        q = q->next;
        p = p->next;
      }

      return ret;
    }
};


int main() {
  Solution s;
  ListNode *head = new ListNode(1);
  head->next = new ListNode(4);
  head->next->next = new ListNode(6);
  head->next->next->next = new ListNode(8);
  head->next->next->next->next = head->next->next->next;
  ListNode *p = s.detectCycle(head);
  cout << (p ? p->val : 0) << endl;
  return 0;
}
