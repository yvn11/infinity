#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();

        for (int i = 0; i < pow(2, n); ++i) {
            vector<int> v;
            for (int j = 0; j < n; ++j) {
              if ((i & (1<<j)) == 0) {
                v.push_back(nums[j]);
              }
            }
            if (find(ret.begin(), ret.end(), v) == ret.end())
              ret.push_back(v);
        }

        return ret;
    }
};


int main() {
  Solution s;
  vector<int> v = {1,2,3};
  for (auto v : s.subsets(v)) {
    for (auto n : v) {
      cout << n << ',';
    }
    cout << endl;
  }
  return 0;
}
