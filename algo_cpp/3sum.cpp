#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;

        if (nums.size() < 3) {
            return ret;
        }
        
        sort(nums.begin(), nums.end());
        set<vector<int> > mem;

        if (nums[nums.size()-1] == nums[0]) {
            if (nums[0] == 0) {
                vector<int> v = {nums[0], nums[0], nums[0]};
                ret.push_back(v);
            }
            return ret;
        }

         
        for (int x = 0; x < nums.size()-2; ++x) {
            int i = x+1, j = nums.size()-1;
            while (i < j) {
                if (nums[x]+nums[i]+nums[j] == 0) {
                      vector<int> v = {nums[x], nums[i], nums[j]};
                      if (mem.find(v) == mem.end()) {
                        ret.push_back(v);
                        mem.insert(v);
                      }
                }
                if (nums[x]+nums[i]+nums[j] < 0)
                    i++;
                else
                    j--;
            }
        }

        return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {-1, 0, 1, 2, -1, -4};
  v = {0,-4,-1,-4,-2,-3,2};
  v = {-4,-1,-4,0,2,-2,-4,-3,2,-3,2,3,3,-4};

  for (auto v: s.threeSum(v)) {
    for (auto x: v) {
      cout << x << ' ';
    }
    cout << '\n';
  }
  return 0;
}
