#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 3) {
            return INT_MIN;
        }
        
        int ret = INT_MAX-target;
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size()-2; ++i) {
            int l = i+1, r = nums.size()-1;

            while (l < r) {
                int v = nums[i]+nums[l]+nums[r];
                if (abs(target-ret) > abs(target-v)) {
                    ret = v;
                }

                if (v < target) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        
        return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {1,1,-1,-1,3};
  int t = -1;
  cout << s.threeSumClosest(v, t) << '\n';
  return 0;
}
