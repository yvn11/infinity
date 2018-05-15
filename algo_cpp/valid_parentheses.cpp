#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> mem;
        
        if (s.length() == 0) {
            return true;
        }
        
        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];
            
            switch (c) {
                case ')': {
                    if (mem.empty()) 
                      return false;
                    char t = mem.top();
                    while (t != '(' && !mem.empty()) {
                        if (t == '[' or t == '{') 
                          return false;
                        mem.pop();
                        t = mem.top();
                    }
                    if (mem.empty() && t != '(') {
                      return false;
                    }
                    mem.pop();
                    break;
                };
                case ']': {
                    if (mem.empty()) 
                      return false;
                    char t = mem.top();
                    while (t != '[' && !mem.empty()) {
                        if (t == '(' or t == '{') 
                          return false;
                        mem.pop();
                        t = mem.top();
                    }
                    if (mem.empty() && t != '[') {
                      return false;
                    }
                    mem.pop();
                    break;
                };
                case '}': {
                    if (mem.empty()) 
                      return false;
                    char t = mem.top();
                    while (t != '{' && !mem.empty()) {
                        if (t == '(' or t == '[') 
                          return false;
                        mem.pop();
                        t = mem.top();
                    }
                    if (mem.empty() && t != '{') {
                      return false;
                    }
                    mem.pop();
                    break;
                };
                case '(':
                case '[':
                case '{':
                    mem.push(c);
                    break;
            }
        }
        
        return mem.empty();
    }
};

int main() {
  Solution s;
  cout << bool(s.isValid("([)]")) << '\n';
  cout << bool(s.isValid("{}{}()[]")) << '\n';
  return 0;
}
