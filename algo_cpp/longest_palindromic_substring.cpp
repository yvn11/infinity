#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  
  string n2(string s) {
    if (s.empty())
        return s;

    int n = s.length();

    vector<vector<bool>> mem(n, vector<bool>(n, false));
    string ret(s.substr(0,1));
    mem[0][0] = true;

    for (int i = 1; i<n; ++i) {
      mem[i][i] = true;
      mem[i-1][i] = s[i] == s[i-1];

      if (mem[i-1][i] && ret.length() < 2)
         ret = s.substr(i-1, 2);
    }

    for (int l = 3; l <= n; ++l)
      for (int j = 0; j + l -1 < n; ++j) {
        int end = j+l-1;
        mem[j][end] = mem[j+1][end-1] && s[j] == s[end];
        if (mem[j][end] && ret.length() < l)
            ret = s.substr(j, l);
      }

    return ret;
  }

  string longestPalindrome(string s) {
    return n2(s);
  }
};

int main() {
  Solution s;
  cout << s.longestPalindrome("igglaalggiabdce") << endl;
  cout << s.longestPalindrome("acca") << endl;
  cout << s.longestPalindrome("adcba") << endl;
  cout << s.longestPalindrome("bbb") << endl;
  cout << s.longestPalindrome("cccc") << endl;
  cout << s.longestPalindrome("babad") << endl;
  cout << s.longestPalindrome("cbbd") << endl;
  return 0;
}

