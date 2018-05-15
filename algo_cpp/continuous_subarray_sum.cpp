#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int sum = 0;
        unordered_map<int, int> mem;
        mem[0] = -1;
        
        for (int i = 0; i < nums.size(); ++i) {
          sum += nums[i];
          if (k != 0) sum %= k;
          if (mem.find(sum) != mem.end()) {
            if (i-mem[sum] > 1)
              return true;
          } else
            mem[sum] = i;
        }
        
        return false;
    }
};


int main() {
  Solution s;
  vector<int> v = {0, 0};
  //{23, 2, 4, 6, 7};
  int k = 0;
  cout << s.checkSubarraySum(v, k) << endl;
  return 0;
}
