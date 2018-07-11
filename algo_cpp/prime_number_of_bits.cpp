#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool is_prime(int n, unordered_set<int> &mem) {
      if (n == 1)
        return false;

      if (mem.find(n) != mem.end())
        return true;

      for (int i = 2; i*i <= n; ++i) {
        if (n%i == 0)
          return false;
      }

      mem.insert(n);
      return true;
    }
  
    int countPrimeSetBits(int L, int R) {
      int ret = 0;  
      unordered_set<int> mem;

      while (L <= R) {
        int c = __builtin_popcount(L++);
        ret += is_prime(c, mem) ? 1 : 0;
      }
      return ret;
    }
};


int main() {
  Solution s;
  cout << s.countPrimeSetBits(6, 10) << endl;
  return 0;
}
