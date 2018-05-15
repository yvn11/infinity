#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        if (nums.empty())
            return false;

        unordered_map<int, int> mem;
        for (int i = 0; i < nums.size(); ++i) {
            if (mem.find(nums[i]) != mem.end()) {
                if (i-k <= mem[nums[i]]) {
                    return true;
                }
            }
            mem[nums[i]] = i;
        }
        return false;
    }
};


int main() {
  Solution s;
  vector<int> v = {1, 2, 1};
  cout << s.containsNearbyDuplicate(v, 1);
  return 0;
}
