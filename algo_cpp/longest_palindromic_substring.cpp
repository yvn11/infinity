#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  
  string old_school(string s) {
    vector<vector<bool>> mem(s.length(), vector<bool>(s.length(), false));
    int begin=0, mlen=1;
    
    for (int i = 0; i < s.length(); ++i) {
      mem[i][i] = true;
    }

    for (int i = 0; i < s.length()-1; ++i) {
      if (s[i] == s[i+1]) {
        mem[i][i+1] == true;
        mlen = 1;
        begin = i;
      }
    }

    for (int l = 3; l <= s.length(); ++l) {
      for (int i = 0; i < s.length()-l+1; ++i) {
        int j = i + l -1;
        if (mem[i+1][j-1] && s[i] == s[j]) {
          mem[i][j] == true;
          if (l > mlen) {
            mlen = l;
            begin = i;
          }
        }
      }
    }
    
    return s.substr(begin, mlen);
  }

  string linear(string s) {
    int mlen = 1, cur = 1, i, j = 0;

    if (s.length() == 1)
      return s;

    if (s.length() == 2)
      return s[0] == s[1] ? s : s.substr(0, 1);
    int l = 0, r = 3;
    for (i = 2; i < s.length();) {
      cur = 0; l = 0; r = 3;
      
      if (s[i] == s[i-2]) {
        cur = 3; l = i-2; r = i;
      }
      if (s[i] == s[i-1]) {
        cur = 2; l = i-1; r = i;
      }

      if (cur > 1) {
      //while (i-cur+1 >= 0 && s[i] == s[i-cur+1] && i < s.length()) {
      while (l >= 0 && r < s.length() && s[l] == s[r]) {
        cur = r-l+1;
        if (cur > mlen) {
          mlen = cur;
          j = l;
        }
        l--; r++;
      }
      i = r;
      }
      else i++;
    }

    return mlen > 1 ? s.substr(j, mlen) : s.substr(0, 1);
  }

  string longestPalindrome(string s) {
    return this->old_school(s);
    //return this->linear(s);
  }
};

int main() {
  Solution s;
  cout << s.longestPalindrome("igglaalggiabdce") << '\n';
  cout << s.longestPalindrome("acca") << '\n';
  cout << s.longestPalindrome("adcba") << '\n';
  cout << s.longestPalindrome("bbb") << '\n';
  cout << s.longestPalindrome("cccc") << '\n';
  cout << s.longestPalindrome("babad") << '\n';
  cout << s.longestPalindrome("cbbd") << '\n';
  return 0;
}

