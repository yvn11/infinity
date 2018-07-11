#include <iostream>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
      if (s.empty())
        return 0;

      int i = s.length()-1;
      
      while (s[i] >= 0 && s[i] == ' ') --i;
      if (i == -1)
        return 0;

      int last = i;
      while (i >= 0 && s[i] != ' ') --i;
      
      return last-i;
    }
};

int main() {
  Solution s;
  cout << s.lengthOfLastWord("hello world") << endl;
  cout << s.lengthOfLastWord("world") << endl;
  cout << s.lengthOfLastWord("world ") << endl;
  cout << s.lengthOfLastWord(" ") << endl;
  return 0;
}
