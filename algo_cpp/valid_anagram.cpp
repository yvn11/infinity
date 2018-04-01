#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
          return false;
        
        vector<int> mem(26, 0);

        for (auto c : s) {
            mem[c-'a']++;
        }
        
        for (auto c : t) {
            mem[c-'a']--;
        }
        
        for (int i = 0; i < mem.size(); ++i) {
            if (mem[i] != 0)
              return false;
        }
        
        return true;
    }
};

int main() {
  Solution s;
  cout << s.isAnagram("anagram", "nagaram") << endl;
  cout << s.isAnagram("rat", "car") << endl;
  return 0;
}
