#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty())
            return 0;
        int ret = nums.size()+1;
        vector<int> mem(nums.size()+1, 0);
        
        for (int i = 0; i < nums.size(); ++i) {
            mem[i] = nums[i];
            if (mem[i] >= s) {
              ret = 1;
            }
        }

        for (int l = 2; l <= nums.size(); ++l) {
            int c = ret;
            for (int i = 0; i+l-1 < nums.size(); ++i) {
                mem[i] = mem[i]+nums[i+l-1];
                if (mem[i] >= s) {
                  c = l;
                }
            }
            ret = min(ret, c);
        }
        
        return ret > nums.size() ? 0 : ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {2,3,1,2,4,3};
  int k = 7;
  cout << s.minSubArrayLen(k, v);
  return 0;
}
