#include <iostream>
using namespace std;

class Solution {
public:
  
  string longestPalindrome(string s) {
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
};

int main() {
  Solution s;
  cout << s.longestPalindrome("acca") << '\n';
  cout << s.longestPalindrome("adcba") << '\n';
  return 0;
}

