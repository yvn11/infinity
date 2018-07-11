#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
      int ret = 1, j = 1;
      size_t i = 0;
      if (nums.empty())
        return ret;
      
      sort(nums.begin(), nums.end());
      while (j <= nums.back() && i < nums.size()) {
        if (j < nums[i]) {
          if (i == 0 || j > nums[i-1]) {
            ret = j;
            break;
          } else {
            ++j;
          }
        } else {
          ++i;
        }
      }
      
      if (j == nums.back()) 
        ret = ++j;
      return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {1,5,3,3,7};
  cout << s.firstMissingPositive(v) << endl;
  return 0;
}
