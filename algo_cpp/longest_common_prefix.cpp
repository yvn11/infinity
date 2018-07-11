#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret;
        int cur = 0;
        
        if (strs.size() == 0) {
            return ret;
        }
        
        while (cur < strs[0].length()) {
            char c = -1;
            for (string &s : strs) {
                if (cur >= s.length()) {
                    return ret;
                }
                if (c == -1) {
                    c = s[cur];
                } else {
                    if (s[cur] != c) {
                        return ret;
                    }
                }
            }
            ret += c;
            cur++;
        }
        
        return ret;
    }
};

int main() {
  Solution s;
  vector<string> v = {"abc", "ab", "abcd"};
  cout << s.longestCommonPrefix(v) << '\n';
  return 0;
}
