#include <iostream>

using namespace std;

class Solution {
public:
    int builtin_trick(uint32_t n) {
      return __builtin_popcount(n); 
    }

    int loop_count(uint32_t n) {
      int ret = 0;
      while (n) {
        ++ret;
        n = n & (n-1);
      }
      return ret;
    }
    int hammingWeight(uint32_t n) {
      //return builtin_trick(n);
      return loop_count(n);
    }
};


int main() {
  Solution s;
  cout << s.hammingWeight(128) << endl;
  cout << s.hammingWeight(11) << endl;
  return 0;
}
