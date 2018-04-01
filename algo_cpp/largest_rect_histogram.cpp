#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
      if (heights.empty())
        return 0;
      
      int n = heights.size();
      vector<vector<int>> mem(n+1, vector<int>(n, 0));
      int ma = 0;

      for (int i = 0; i < n; ++i) {
        mem[1][i] = heights[i];
        ma = max(ma, mem[1][i]);
      }

      for (int i = 0; i <= n; ++i) {
        for (int l = 2; i+l <= n; ++l) {
          mem[l][i] = min(mem[l-1][i], heights[i+l-1]);

          if (mem[l][i]*l > ma) {
            ma = mem[l][i]*l;
          }
        }
      }
      return ma;
    }
};

int main() {
  Solution s;
  vector<int> v = {
    2,1,5,6,2,3};
  cout << s.largestRectangleArea(v) << endl;
  return 0;
}
