#include<iostream>
#include<vector>
#include<map>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> ret;
    map<int, int> mem;

    for (int i = 0; i < nums.size(); i++) {
        int n = nums[i];

        if (mem.count(target-n) != 0) {
            ret.push_back(mem[target-n]);
            ret.push_back(i);
            return ret;
        }
        mem[n] = i;
    }

    return ret;
}

int main() {
  vector<int> nums = {3, 4, 2};
  for (auto n : twoSum(nums, 6)) {
      cout << n << '\n';
      }
  return 0;
}
