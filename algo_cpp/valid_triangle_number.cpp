#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.empty())
            return 0;

        int ret = 0;
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i+1; j < nums.size(); ++j) {
                for (int k = j+1; k < nums.size(); ++k) {
                    if (nums[i]+nums[j] > nums[k]) {
                        ret++;
                    }
                }
            }
        }
        
        return ret;
    }
};


int main() {
  Solution s;
  vector<int> v = {2,3,4,5,6,9};
  cout << s.triangleNumber(v) << endl;
  return 0;
}
