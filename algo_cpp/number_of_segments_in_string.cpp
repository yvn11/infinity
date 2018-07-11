#include <iostream>

using namespace std;

class Solution {
public:
    int countSegments(string s) {
      int ret = 0;

      for (int i = 0; i < s.length(); ++i) {
        if (s[i] != ' ' && i == s.length()-1) {
          ++ret;
        } else if (i > 0 && s[i] == ' ' && s[i-1] != ' ') {
          ++ret;
        } 
      }
      return ret;
    }
};


int main() {
  Solution s;
  cout << s.countSegments("the sky is blue, yes it's true") << endl;
  cout << s.countSegments("                           ") << endl;
  cout << s.countSegments("a") << endl;
  cout << s.countSegments("  a  ") << endl;
  return 0;
}
