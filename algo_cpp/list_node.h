#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void print_list(ostream &o, ListNode* head) {
  ListNode* p = head;
  while (p) {
    o << p->val << ',';
    p = p->next;
  }
  o << endl;
}
