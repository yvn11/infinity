#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterComb(string digits, map<string, vector<string> > &mem) {
        vector<string> ret;
        string k = digits;

        if (k.length() == 0) {
          return ret;
        }

        if (mem.find(k) != mem.end()) {
            return mem[k];
        }
        
        if (k.length() == 2) {
            vector<string> l1 = mem[k.substr(0, 1)], l2 = mem[k.substr(1, 1)];
            vector<string> v;

            for (int i = 0; i < l1.size(); ++i) {
                for (int j = 0; j < l2.size(); ++j) {
                    v.push_back(l1[i]+l2[j]);
                }
            }
            
            mem.insert(pair<string, vector<string> > (k, v));
            return mem[k];
        }

        int n = digits.length();
        vector<string> v = this->letterComb(k.substr(0, n-1), mem);
        vector<string> vk;
        for (auto x : v) {
          for (auto e : mem[k.substr(n-1,1)]) {
              string s = x.substr(0, x.length()) + e.substr(0, e.length());
              vk.push_back(s);
          }
        }
                                            
        mem.insert(pair<string, vector<string> > (k, vk));
        return vk;
    }
    
    vector<string> letterCombinations(string digits) {
        map<string, vector<string> > mem = {
            {"2", {"a", "b", "c"}},
            {"3", {"d", "e", "f"}},
            {"4", {"g", "h", "i"}},
            {"5", {"j", "k", "l"}},
            {"6", {"m", "n", "o"}},
            {"7", {"p", "q", "r", "s"}},
            {"8", {"t", "u", "v"}},
            {"9", {"w", "x", "y", "z"}},
        };
        return this->letterComb(digits, mem);
    }
};

int main() {
  Solution s;
  string d("452");

  for (auto v : s.letterCombinations(d)) {
    cout << v << endl;
  }
  return 0;
}
