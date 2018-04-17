#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    void get_permutations(string s, set<string>& perm,
                          int begin, int end) {
      cout << begin << ',' << end << ',' << s << endl;
        if (begin == end) {
            perm.insert(s);
            return;
        }
        
        for (int i = begin; i <= end; ++i) {
            swap(s[begin], s[i]);
            get_permutations(s, perm, begin+1, end);
            swap(s[begin], s[i]);
        }
    }
    
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> count;
        
        for (auto c : s1) {
          count[c]++;
        }

        for (int i = 0; i+s1.length()-1 < s2.length();++i) {
            string s = s2.substr(i,s1.length());
            unordered_map<char, int> t;
            for (auto c : s)
              t[c]++;
            if (count == t)
              return true;
            
        }
        
        return false;
    }
};


int main() {
  Solution s;
  cout << s.checkInclusion("ab", "wrwrwrbawrw") << endl;
  cout << s.checkInclusion("adc", "dcda") << endl;
  cout << s.checkInclusion("dinitrophenylhydrazine",
    "acetylphenylhydrazine") << endl;
  return 0;
}

