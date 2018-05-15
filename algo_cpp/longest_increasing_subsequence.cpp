#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


class Solution {
public:
    int max(vector<int> &mem, int begin, int end, int val) {
      while (end-begin > 1) {
        int m = (begin + end)/2;
        if (mem[m] >= val) {
          end = m;
        } else {
          begin = m;
        }
      }
      return end;
    }

    int lengthOfLIS(vector<int>& nums) {
      if (nums.empty()) 
        return 0;

      vector<int> mem(nums.size(), 0);
      int len = 1;
      mem[0] = nums[0];
       
      for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < mem[0]) {
          mem[0] = nums[i];
        } else if (nums[i] > mem[len-1]) {
          mem[len++] = nums[i];
        } else {
          mem[this->max(mem, -1, len-1, nums[i])] = nums[i];
        }
      }
      return len;
    }
};


int main() {
  Solution s;
  vector<int> v = 
    //{10, 9, 2, 5, 3, 7, 101, 18};
  {4,10,4,3,8,9};
  cout << s.lengthOfLIS(v) << endl;
  return 0;
}
