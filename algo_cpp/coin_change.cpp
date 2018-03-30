#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;


class Solution {
public:
    int do_change(vector<int>& coins, int amount) {
        if (amount == 0)
          return 0;
        
        int total = INT_MAX;

        for (int i = 0; i < coins.size() && coins[i] <= amount; ++i) {
          int ret = this->do_change(coins, amount-coins[i]);
          if (ret != INT_MAX && ret + 1 < total)
            total = ret + 1;
        }

        return total;
    }

    int coinChange(vector<int>& coins, int amount) {
      if (!coins.size())
        return -1;
      
      vector<int> mem(amount+1, INT_MAX);
      mem[0] = 0;

      for (int i = 1; i < mem.size(); ++i) {
        for (int j = 0; j < coins.size(); ++j) {
          if (coins[j] > i)
            continue;

          int prev = mem[i-coins[j]];
          if (prev != INT_MAX && prev + 1 < mem[i]) {
            mem[i] = prev + 1;
          }
        }
      }
      
      return mem[amount] == INT_MAX ? -1 : mem[amount];
    }
};

int main() {
  Solution s;
  vector<int> v = {186,419,83,408};
  int a = 6249;

  cout << s.coinChange(v, a) << endl;
  return 0;
}
