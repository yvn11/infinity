#include <iostream>
#include <queue>
#include "list_node.h"

using namespace std;

struct compare {
  bool operator() (const ListNode* a, const ListNode* b) const {
    return a->val > b->val;
  }  
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
      priority_queue<ListNode*, vector<ListNode*>, compare> q;
      for (auto n : lists) {
        if (n)
          q.push(n);
      }
      
      ListNode *ret = new ListNode(0);
      ListNode *t = ret;
      
      while (!q.empty()) {
        t->next = q.top();
        q.pop();
        t = t->next;
        if (t->next) {
          q.push(t->next);
        }
      }
      
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

  ListNode* l3 = new ListNode(3);
  p = l3;
  for (int i = p->val; i < 17; p = p->next)
    p->next = new ListNode(++i);

  vector<ListNode*> v = {l1, l2, l3};
  ListNode* head = s.mergeKLists(v);
  print_list(cout, head);
  return 0;
}
