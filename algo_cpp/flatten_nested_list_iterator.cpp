#include <iostream>
#include <vector>
#include <queue>
#include "nested_integer.h"

using namespace std;


class NestedIterator {
private:
    queue<int> mem;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        init(nestedList, mem);
    }
    
    void init(const vector<NestedInteger> &nlist, queue<int> &mem) {
        for (auto &n : nlist) {
            if (n.isInteger()) {
                mem.push(n.getInteger());
            } else {
                init(n.getList(), mem);
            }
        }
    }

    int next() {
        int ret = mem.front();
        mem.pop();
        return ret;
    }

    bool hasNext() {
        return !mem.empty();
    }
};


int main() {
  vector<NestedInteger> v;
  for (int i = 0; i < 5; ++i) 
    v.push_back(NestedInteger(i+1));

  vector<NestedInteger> outter(v);
  outter.push_back(NestedInteger(88));
   
  NestedIterator it(outter);

  while (it.hasNext()) {
    cout << it.next() << ',';
  }
  cout << endl;
  return 0;
}
