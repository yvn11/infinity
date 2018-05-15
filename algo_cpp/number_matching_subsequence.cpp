#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool is_subsequence(string s, string t) {
      if (s.length() > t.length())
        return false;
        
      int i = 0, j = 0;
      while (i < s.length() && j < t.length()) {
        if (s[i] == t[j++]) {
          i++;
        }
      }

      return i == s.length();
    }

    int numMatchingSubseq(string S, vector<string>& words) {
      int ret = 0;
      unordered_map<string, bool> mem;

      for (auto w : words) {
        if (mem.find(w) != mem.end()) {
            ret += mem[w] ? 1 : 0;
        } else if (this->is_subsequence(w, S)) {
            ret++;
            mem.insert(make_pair(w, true));
        } else {
            mem.insert(make_pair(w, false));
        }
      }
      return ret;
    }
};

int main() {
  Solution s;
  string a("abcde");
  vector<string> v = {"a", "bb", "acd", "ace", "ace", "ace", "ace", "ace"};
  cout << s.numMatchingSubseq(a, v) << endl;
  return 0;
}

