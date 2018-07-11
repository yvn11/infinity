#include <iostream>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
      int i = 0, j = 0, k = 0; 
      while (i < s.length()) {
        if (i != s.length()-1 && s[i+1] != ' ') {
          ++i;
          continue;
        }

        k = i+1;

        while (j < i)
          swap(s[i--], s[j++]);
        
        i = k+1;
        j = i;
      }
      return s;
    }
};

int main() {
  Solution s;
  cout << "fak fill and kill, tick size" << endl;
  cout << s.reverseWords("fak fill and kill, tick size") << endl;
  cout << s.reverseWords("") << endl;
  cout << s.reverseWords("ab,") << endl;
  return 0;
}
