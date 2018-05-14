#include <iostream>

using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        if (n == 0)
            return n;

        uint32_t ret = 0;
        int i = 0;
        while (i < 32) {
            if (n & (1<<i)) 
                ret |= 1 << (31-i);
            ++i;
        }
        return ret;
    }
};


int main() {
  Solution s;
  cout << s.reverseBits(7) << endl;
  return 0;
}
