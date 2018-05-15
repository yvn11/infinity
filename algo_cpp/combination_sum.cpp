#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    void find_nums(vector<int> &cand, int target, int ind,
                   vector<vector<int>> &mem, vector<int> &cur) {
        if (target == 0) {
            mem.push_back(cur);
            return;
        }
        
        if (cand.size() == 0 || target < 0) {
            return;
        }
        
        while (ind < cand.size()) {
            cur.push_back(cand[ind]);
            this->find_nums(cand, target-cand[ind], ind, mem, cur);
            ind++;
            cur.pop_back();
        }
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ret;
        vector<int> cur;
        this->find_nums(candidates, target, 0, ret, cur);
        return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {2,3,4,5,7};
  for (auto vn : s.combinationSum(v, 8)) {
    for (auto n : vn) {
      cout << n << ',';
    }
    cout << endl;
  }
  return 0;
}
