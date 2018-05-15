#include <iostream>

using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
      if (s.empty()) 
        return false;
      int i = 0, len = 1;

      auto size = s.length()/2;
      while (len <= size) {
        i = 0;
        if (s.length() % len == 0) {
          while (i+len < s.length() && s[i] == s[i+len])
            ++i;
          if (i + len == s.length())
            return true;
        }
        ++len;
      }
      return false;
    }
};

int main() {
  Solution s;
  cout << s.repeatedSubstringPattern("aabaaba") << endl;
  return 0;
}
