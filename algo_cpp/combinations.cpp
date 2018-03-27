#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

class Solution {
public:
    void do_combine(int n, int k, set<vector<int>> &mem,
                   vector<int> &cur, int ind) {
        if (cur.size() == k) {
            mem.insert(cur);
            return;
        }
        
        for (int i = ind; i <= n; ++i) {
            cur.push_back(i);
            this->do_combine(n, k, mem, cur, i+1);
            cur.pop_back();
        }    
    }
    
    vector<vector<int>> combine(int n, int k) {
        set<vector<int>> ret;
        vector<int> cur;
        
        this->do_combine(n, k, ret, cur, 1);
        return vector<vector<int>>(ret.begin(), ret.end());
    }
};

int main() {
  Solution s;
  for (auto v : s.combine(6, 3)) {
    for (auto n : v) {
      cout << n << ',';
    }
    cout << endl;
  }

  return 0;
}
