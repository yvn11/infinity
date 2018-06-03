#include <iostream>

using namespace std;

class Solution {
public:
    string final_str(string s) {
      string ret;
      for (int i = 0; i < s.length(); ++i) {
        if (s[i] != '#') {
          ret += s[i];
          continue;
        }
        if (!ret.empty())
          ret.pop_back();
      }
      return ret;
    }
    bool backspaceCompare(string S, string T) {
      return final_str(S) == final_str(T);
    }
};


int main() {
  Solution s;
  cout << s.backspaceCompare("a##b", "a#b#");
  return 0;
}
