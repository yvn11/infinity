#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4)
          return vector<vector<int>>();

        set<vector<int>> ret;
        unordered_map<int, set<pair<int, int>>> mem;
        int n = nums.size();

        for (int i = 0; i < n-1; ++i) {
          for (int j = i+1; j < n; ++j) {
            int sum = nums[i] + nums[j];

            if (mem.find(target-sum) != mem.end()) {
              for (auto comb : mem[target-sum]) {
                if (comb.first != i && comb.first != j
                  && comb.second != i && comb.second != j) {
                  vector<int> v{nums[comb.first], nums[comb.second], nums[i], nums[j]};
                  sort(v.begin(), v.end());
                  ret.insert(v);
                }
              }
            }
            else {
              pair<int, int> p = {i, j};
              if (mem[sum].find(p) == mem[sum].end()) 
                mem[sum].insert(p);
            }
          }
        }

        vector<vector<int>> ret2;
        for (auto v : ret) {
          ret2.push_back(v);
        }
        return ret2;
    }
};

int main() {
  Solution s;
  vector<int> v = 
    {-3, -1, 0, 2, 4, 5};
    //{1, 0, -1, 0, -2, 2};
    //{-5,-4,-3,-2,-1,0,0,1,2,3,4,5};
  int t = 0;
  vector<vector<int>> r = s.fourSum(v, t);

  for (auto x : r){
    for (auto i : x) {
      cout << i << ',';
    }
    cout << endl;
  }
  cout << r.size() << endl;
  return 0;
}
