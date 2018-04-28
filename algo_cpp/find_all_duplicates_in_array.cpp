#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ret;
        for (int i = 0; i < nums.size(); ++i) {
            int j = abs(nums[i]);
            if (nums[j-1] > 0) {
                nums[j-1] = -nums[j-1];
            } else {
                ret.push_back(j);
            }
        }
        return ret;
    }
};


int main() {
  Solution s;
  vector<int> v = {3,5,1,1,3,3,4};
  for (auto n : s.findDuplicates(v)) {
    cout << n << ',';
  }
  cout << endl;
  return 0;
}
