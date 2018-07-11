#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


class Solution {
public:
    void findCircle(vector<vector<int>> &M,
        vector<bool> &mem, int begin) {
      if (mem[begin])
        return;
      mem[begin] = true;

      for (int i = 0; i < M.size(); ++i) {
        if (M[begin][i]) {
          findCircle(M, mem, i);
        }
      }
    }

    int findCircleNum(vector<vector<int>>& M) {
        if (M.empty())
            return 0;
        
        int ret = 0;
        vector<bool> mem(M.size(), false);

        for (int i = 0; i < M.size(); ++i) {
          if (mem[i])
            continue;
          findCircle(M, mem, i);
          ++ret;
        }

        return ret;
    }
};

int main() {
  Solution s;
  vector<vector<int>> v = {
 //   {1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}
 //   {1,1,0},{1,1,0},{0,0,1}
{1,1,0,0,0,0,0,1,0,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,1,1,0,0,0,0},
{0,0,0,1,0,1,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,1,0,1,0,0,0,0,1,0},
{1,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0,1,0},
{0,0,0,0,1,0,0,0,0,1,0,1,0,0,1},
{0,0,0,0,1,1,0,0,0,0,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,1,0,0,0,0,1}
  };
  cout << s.findCircleNum(v);
  return 0;
}
