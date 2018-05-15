#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ret;
        
        if (s.length() < 10)
            return ret;
        
        unordered_map<string, int> mem;
        for (int i = 0; i <= s.length()-10; ++i) {
            if (mem.find(s.substr(i, 10)) != mem.end()) {
              if (mem[s.substr(i, 10)] < 2)
                ret.push_back(s.substr(i, 10));
            }
            mem[s.substr(i, 10)]++;
        }
        
        return ret;
    }
};


int main() {
  Solution s;
  for (auto v : s.findRepeatedDnaSequences("AAAAAAAAAAAA")) {
    cout << v << ',';
  }
  cout << endl;
  return 0;
}
