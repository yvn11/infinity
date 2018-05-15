#include <iostream>
#include <map>
#include <vector>
#include <numeric>

using namespace std;


class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        map<int, int> mem{{0, 0}};
        for (int i = 0; i < difficulty.size(); ++i) 
          mem[difficulty[i]] = max(mem[difficulty[i]], profit[i]);
      
        for (auto it = next(mem.begin()); it != mem.end(); ++it) 
          it->second = max(it->second, prev(it)->second);
      
        return accumulate(worker.begin(), worker.end(), 0, 
                          [&](int sum, int w) {return sum + prev(mem.upper_bound(w))->second;});
    }
};


int main() {
  Solution s;
  vector<int> d = {2,4,6,8,10};
  vector<int> p = {10,20,30,40,50};
  vector<int> w = {4,5,6,7};
  cout << s.maxProfitAssignment(d, p, w);
  return 0;
}
