#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int bit_count(vector<int>& nums) {
      int ret = 0;

      for (int i = 0; i < INT_MAX; ++i) {
        int sum = 0;
        int mask = 1 << i;

        for (int j = 0; j < nums.size(); ++j) {
            if (nums[j] & mask)
              sum++;
        }
        if (sum % 3)
          ret |= mask;
      }
      return ret;
    }

    int hash_count(vector<int>& nums) {
      int ret = 0;
      unordered_map<int, int> mem;

      for (int i = 0; i < nums.size(); ++i) {
        mem[nums[i]] += 1;
      }

      for (int i = 0; i < nums.size(); ++i) {
        if (mem[nums[i]] == 1) {
          ret = nums[i];
          break;
        }
      }
      return ret;
    }

    int singleNumber(vector<int>& nums) {
      return hash_count(nums);
    }
};

int main() {
  Solution s;
  vector<int> v = {2,2,2,3};
  cout << s.singleNumber(v) << endl;
  return 0;
}
