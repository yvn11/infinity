#include <iostream>
#include <math.h>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        char c, pc, last;
        bool ret = false;
        int i = 0, j = 0;
        
        if (p == ".*") {
            return true;
        }
        
        for (; i < s.length() && j < p.length();) {
            c = s[i];
            pc = p[j];
            
            if (pc == '.') {
                if (j == 0)
                    return false;
                j++;i++;
                last = pc;
                continue;
            }
            
            if (pc == '*') {
                j++;
                pc = p[j];
                if (last == '.') {
                    if (j < p.length()) {
                        while (s[i] != pc && i < s.length()) i++;
                    }
                    i = s.length();
                    break;
                } else {
                    while (s[i] == last && i < s.length()) i++;
                    if (pc == last)
                      j++;
                    cout << i << ' ' << j << '\n';
                }
                continue;
            }
            
            if (c == pc) {
                j++;i++;
                last = pc;
                continue;
            }
            j++;
            last = pc;
        }
        return (i == s.length() && j == p.length());        
    }
};


int main() {
  Solution s;
  cout << s.isMatch("bccaabcacbacaccca", "b*.*baa*b*.a*bc*c") << '\n';
  cout << s.isMatch("aabb", "c*a*b*") << '\n';
  cout << s.isMatch("aabb", "d*") << '\n';
  cout << s.isMatch("aaa", "a*a") << '\n';
  cout << s.isMatch("aaa", "ab*a") << '\n';
  cout << s.isMatch("aaa", "ab*a*c*a") << '\n';
  return 0;
}
