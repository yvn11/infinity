#include <iostream>
using namespace std;

class Solution {
public:
  
  string old_school(string s) {
    bool mem[s.length()][s.length()];
    int begin=0, max_len=1;
    
    for (int i = 0; i < s.length(); ++i) {
      mem[i][i] = true;
    }
    
    for (int i = 0; i+1 < s.length(); ++i) {
      if (s[i] == s[i+1]) {
        mem[i][i+1] = true;
        begin = i;
        max_len = 2;
      }
    }
    
    for (int l = 3; l <= s.length(); ++l) {
      for (int i = 0; i < s.length()-l+1; ++i) {
        int j = i + l -1;
        
        if (mem[i+1][j-1] && s[i] == s[j]) {
          mem[i][j] == true;
          if (l > max_len) {
            max_len = l;
            begin = i;
          }
        }
      }
    }
    
    return s.substr(begin, max_len);
  }

  string linear(string s) {
    int mlen = 1, cur = 0, i, j;

    if (s.length() == 1)
      return s;

    if (s.length() == 2)
      return s[0] == s[1] ? s.substr(0, 1) : s.substr(1, 1);

    for (i = 0; i < s.length();) {
      if (cur != 0) {
          if (i-cur-1 >= 0 && s[i-cur-1] == s[i]) {
            cur += 2;
          } else {
            if (cur > mlen) {
              mlen = cur;
              j = i-mlen;
            }
            cur = 0;
          }
          i++;
      } else {
          if (i+1 < s.length() && s[i] == s[i+1]) {
            cur += 2;
            i += 2;
          }
          else if (i+2 < s.length() && s[i] == s[i+2]) {
            cur += 3;
            i += 3;
          }
          else
            i++;
        }
      }
            
    if (cur > mlen) {
      mlen = cur;
      j = i-mlen;
    }
    return mlen > 1 ? s.substr(j, mlen) : s.substr(0, mlen);
  }

  string longestPalindrome(string s) {
    //return this->old_school(s);
    return this->linear(s);
  }
};

int main() {
  Solution s;
  cout << s.longestPalindrome("igglaalggiabdce") << '\n';
  cout << s.longestPalindrome("acca") << '\n';
  cout << s.longestPalindrome("adcba") << '\n';
  return 0;
}

