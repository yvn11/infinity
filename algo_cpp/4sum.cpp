#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Mem {
    int sum;
    int l;
    int r;

    Mem(int l, int r, int sum)
        :l(l), r(r), sum(sum)
        {}
};


struct {
    bool operator()(Mem a, Mem b) const {
        return a.sum < b.sum;
    }
} compare_mem;

class Solution {
public:

    bool uniq(Mem &a, Mem &b) {
      return !(a.l == b.l || a.l == b.r ||
                    a.r == b.l || a.r == b.r);
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ret;

        if (nums.size() < 4) {
            return ret;
        }

        vector<Mem> mem;

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i+1; j < nums.size(); ++j) {
                mem.push_back(Mem(i, j, nums[i]+nums[j]));
            }
        }

        sort(mem.begin(), mem.end(), compare_mem);
        set<vector<int>> met;
        int l = 0, r = mem.size()-1;

        while (l < mem.size() && r >= 0) {
            int v = mem[l].sum + mem[r].sum;

            if (v == target) {
                if (this->uniq(mem[l], mem[r])) {
                    vector<int> v = {nums[mem[l].l], nums[mem[l].r],
                      nums[mem[r].l], nums[mem[r].r]};
                    sort(v.begin(), v.end());

                    if (met.find(v) == met.end()) {
                        ret.push_back(v);
                        met.insert(v);
                    }
                }
            }

            if (v < target) {
                l++;
            } else {
                r--;
            }
        }
        return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {-5,-4,-3,-2,-1,0,0,1,2,3,4,5};
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
