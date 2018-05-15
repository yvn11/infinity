#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void do_permute(vector<int> &nums, vector<vector<int>> &mem, 
                    int begin, int end) {
        if (begin == end) {
            mem.push_back(nums);
            return;
        }
         
        for (int i = begin; i <= end; ++i) {
            swap(nums[begin], nums[i]);
            this->do_permute(nums, mem, begin+1, end);
            swap(nums[begin], nums[i]);
        }
    }
    
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ret;
        
        this->do_permute(nums, ret, 0, nums.size()-1);
        return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {1,2,3};

  for (auto vn : s.permute(v)) {
    for (auto n : vn) {
      cout << n << ',';
    }
    cout << endl;
  }
  return 0;
}
