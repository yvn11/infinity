#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    
    bool is_palindrom(string s) {
      int i = 0, j = s.length()-1;
      for (;j > i && s[i] == s[j]; ++i, --j);
      return i >= j ? true : false;
    }

    int countSubstrings(string s) {
        int ret = s.length();
        int len = 0;
        unordered_set<string> mem;
        
        for (int l = 2; l <= s.length(); ++l) {
          for (int i = 0; i + l <= s.length(); ++i) {
            if (mem.find(s.substr(i, l)) != mem.end() || is_palindrom(s.substr(i, l))) {
              ret++;
              mem.insert(s.substr(i, l));
            }
          }
        }
        
        return ret;
    }
};

int main() {
  Solution s;
  cout << s.countSubstrings("bbb") << endl;
  return 0;
}
