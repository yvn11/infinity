#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ret;
        unordered_map<string, int> mem;
        
        for (string &ss : strs) {
            string s(ss);
            sort(s.begin(), s.end());
            
            if (mem.find(s) == mem.end()) {
                vector<string> v = {ss};
                ret.push_back(v);
                mem.insert(make_pair(s, ret.size()-1));
            } else {
                int ind = mem[s];
                ret[ind].push_back(ss);
            }
        }
        return ret;
    }
};

int main() {
  Solution s;
  vector<string> v = {
    "abds", "adfs", "sdrw", "sbad"
  };
  for (auto g: s.groupAnagrams(v)) {
    for (auto s: g) {
      cout << s << ',';
    }
    cout << endl;
  }
  return 0;
}
