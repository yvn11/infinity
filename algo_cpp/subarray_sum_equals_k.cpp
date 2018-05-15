#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    int subarraySum(vector<int> &nums, int k) {
      unordered_map<int, int> mem;
      int sum = 0, ret = 0;
      mem[0] = 1;

      for (int i = 0; i < nums.size(); ++i) {
        // sum_ab = sum[b]-sum[a] == k
        // sum[a] = sum[b]-k
        sum += nums[i];
        if (mem.find(sum-k) != mem.end()) {
          ret += mem[sum-k];
        }
        mem[sum] += 1;
      }
      return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {3,2,5,3,8,6,7};
  int k = 13;
  cout << s.subarraySum(v, k) << endl;
  return 0;
}
