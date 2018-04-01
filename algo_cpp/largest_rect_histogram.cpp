#include <iostream>
#include <vector>
#include <stack>
#include <limits.h>

using namespace std;

class Solution {
public:
    int with_table(vector<int>& heights) {
      if (heights.empty())
        return 0;
      
      int n = heights.size();
      vector<vector<int>> mem(n+1, vector<int>(n, 0));
      int ma = 0;

      for (int i = 0; i < n; ++i) {
        mem[1][i] = heights[i];
        ma = max(ma, mem[1][i]);
      }

      for (int i = 0; i < n; ++i) {
        for (int l = 2; i+l <= n; ++l) {
          mem[l][i] = min(mem[l-1][i], heights[i+l-1]);

          if (mem[l][i]*l > ma) {
            ma = mem[l][i]*l;
          }
        }
      }
      return ma;
    }

    int get_area(stack<int>& mem, vector<int>& heights, int cur) {
      if (mem.empty())
        return 0;
      int t = INT_MAX;
      int c = 0;
      while (!mem.empty()) {
          t = min(t, mem.top());
          mem.pop();
          c++;
      }
      return heights[t] * (mem.empty() ? c : cur-mem.top()-1);
    }

    int with_stack(vector<int>& heights) {
      stack<int> mem;
      int n = heights.size();
      int i = 0, ma = 0;

      while (i < n) {
        if (mem.empty() || heights[mem.top()] <= heights[i]) {
          mem.push(i++);
        } else {
          ma = max(ma, this->get_area(mem, heights, i));
        }
      }
      ma = max(ma, this->get_area(mem, heights, i));
      return ma;
    }

    int largestRectangleArea(vector<int>& heights) {
      //return this->with_table(heights);
      return this->with_stack(heights);
    }
};

int main() {
  Solution s;
  vector<int> v = {
    2,1,5,6,2,3};
  cout << s.largestRectangleArea(v) << endl;
  return 0;
}
