#include <iostream>
#include <stack>
#include <limits.h>

using namespace std;

class MinStack {
private:
    stack<int> _stack;

public:
    MinStack() {
        
    }
    
    void push(int x) {
        int mi = x;
        if (!_stack.empty())
            mi = _stack.top();
        _stack.push(x);
        _stack.push(min(x, mi));
    }
    
    void pop() {
        if (!_stack.empty()) {
            _stack.pop();
            _stack.pop();
        }
    }
    
    int top() {
        int ret = -1;
        
        if (!_stack.empty()) {
            int mi = _stack.top();
            _stack.pop();
            ret = _stack.top();
            _stack.push(mi);
        }
        
        return ret;
    }
    
    int getMin() {
        return _stack.top();
    }
};


int main() {
  MinStack s;
  s.push(-2);
  s.push(-1);
  cout << s.top() << endl;
  cout << s.getMin() << endl;
  s.push(-3);
  cout << s.getMin() << endl;
  return 0;
}
