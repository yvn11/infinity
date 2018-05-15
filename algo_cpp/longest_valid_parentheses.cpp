#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool is_valid(string s) {
        if (s.length() < 2)
          return false;

        int l = 0, r = 0;
        stack<char> st;

        for (auto c : s) {
          if (c == '(')
            st.push(c);
          else if (c == ')') {
            if (!st.empty() && st.top() == '(')
              st.pop();
            else
              st.push(c);
          }
        }
        return st.empty();
    }
    
    int with_mem(string s) {
        int ret = 0;
        vector<vector<int>> mem(s.length(), vector<int>(s.length(), 0));
                
        for (int i = 0; i < s.length() - 1; ++i) {
            mem[i][i+1] = this->is_valid(s.substr(i, 2)) ? 2 : 0;
        }
            
        for (int k = 3; k <= s.length(); ++k) {
            for (int i = 0; i + k <= s.length(); ++i) {
                int n = mem[i][i+k-2] + mem[i+1][i+k-1];
                if (n > s.length() || (i+k-2-(i+1)) > 1 && mem[i+1][i+k-2] == 0)
                    mem[i][i+k-1] = max(mem[i][i+k-2], mem[i+1][i+k-1]);
                else
                    mem[i][i+k-1] = n;
            }
        }

        return mem[0][s.length()-1];
    }

    int linear(string s) {
      int l = 0, r = 0, ret = 0;

      for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(') l++;
        if (s[i] == ')') {
          r++;
        }

        if (r > l) {
          l = 0;
          r = 0;
          continue;
        }

        if (l == r) {
          ret = max(ret, r*2);
        }
      }

      l = r = 0;
      for (int i = s.length()-1; i > 0; --i) {
        if (s[i] == '(') l++;
        if (s[i] == ')') r++;

        if (l > r) {
          l = 0;
          r = 0;
          continue;
        }

        if (l == r) {
          ret = max(ret, r*2);
        }
      }
      return ret;
    }

    int longestValidParentheses(string s) {
        if (s.length() < 2)
            return 0;
        return this->linear(s);
    }
};


int main() {
  Solution s;
  cout << s.longestValidParentheses("(()())") << endl;
  cout << s.longestValidParentheses("()()") << endl;
  cout << s.longestValidParentheses("()(()") << endl;
  cout << s.longestValidParentheses("((()))") << endl;
  cout << s.longestValidParentheses("(()") << endl;
  return 0;
}
