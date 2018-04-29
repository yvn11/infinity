#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        if (s.empty())
            return 0;
        
        int ma = 0, ret = 0;

        vector<int> mem(26, 0);
        
        for (int begin=0, end=0; end < s.size(); ++end) {
            ma = max(ma, ++mem[s[end]-'A']);
            while (end-begin+1-ma > k) {
                --mem[s[begin]-'A'];
                ++begin;
            }
            ret = max(ret, end-begin+1);
        }
        
        return ret;
    }
};


int main() {
  Solution s;
  cout << s.characterReplacement("AABABBA", 1);
  return 0;
}
