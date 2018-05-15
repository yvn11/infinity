#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> mem(cost.size());
        mem[0] = cost[0];
        mem[1] = cost[1];
        
        for (int i = 2; i < cost.size(); ++i) {
            mem[i] = cost[i] + min(mem[i-1], mem[i-2]);
        }
        
        return min(mem[cost.size()-1], mem[cost.size()-2]);
    }
};


int main() {
  Solution s;
  vector<int> v = {0, 1, 1, 0};
  cout << s.minCostClimbingStairs(v) << endl;
  return 0;
}
