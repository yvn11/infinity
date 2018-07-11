#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;


class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> ret(2, 0);
        if (nums.empty())
            return ret;
        
        ret[1] = INT_MAX;
        int k = nums.size();
        vector<int> cache(k, 0);
        bool stop = false;
        
        while (true) {
            int mi = INT_MAX, ma = INT_MIN, ind = 0;

            for (int i = 0; i < k; ++i) {
                if (cache[i] >= nums[i].size()) {
                    stop = true;
                    break;
                }

                if (nums[i][cache[i]] < mi) {
                    mi = nums[i][cache[i]];
                    ind = i;
                }
                
                if (nums[i][cache[i]] > ma) {
                    ma = nums[i][cache[i]];
                }
            }

            if (stop)
              break;
            cache[ind]++;

            if (ma-mi < ret[1]-ret[0]) {
              ret[0] = mi;
              ret[1] = ma;
            }
        }
        
        return ret;
    }
};

int main() {
  Solution s;
  vector<vector<int>> v = {{4,10,15,24,26}, {0,9,12,20}, {5,18,22,30}};

  for (auto r: s.smallestRange(v)) {
    cout << r << ',';
  }
  cout << endl;
  return 0;
}
