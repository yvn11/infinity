#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    int grid_search(vector<vector<int>>& matrix, 
        vector<vector<int>> &mem,
        int m, int n) {
      if (mem[m][n] > -1)
        return mem[m][n];

      int ret = 1;

      if (n < matrix[0].size()-1 && matrix[m][n] < matrix[m][n+1])
        ret = max(ret, 1+this->grid_search(matrix, mem, m, n+1));
      if (m < matrix.size()-1 && matrix[m][n] < matrix[m+1][n])
        ret = max(ret, 1+this->grid_search(matrix, mem, m+1, n));
      if (n > 0 && matrix[m][n] < matrix[m][n-1])
        ret = max(ret, 1+this->grid_search(matrix, mem, m, n-1));
      if (m > 0 && matrix[m][n] < matrix[m-1][n])
        ret = max(ret, 1+this->grid_search(matrix, mem, m-1, n));

      return mem[m][n] = ret;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
       if (matrix.empty())
         return 0;

       int m = matrix.size(), n = matrix[0].size();
       int ret = 0;
       vector<vector<int>> mem(m, vector<int>(n, -1));

       for (int i = 0; i < m; ++i)
         for (int j = 0; j < n; ++j) {
            if (mem[i][j] == -1)
              ret = max(ret, this->grid_search(matrix, mem, i, j));
            else
              ret = max(ret, mem[i][j]);
         }
       return ret;
    }
};

int main() {
  Solution s;
  vector<vector<int>> v = {
  //{9,9,4},{6,6,8},{2,1,1}};
  {3,4,5},{3,2,6},{2,2,1}};
  cout << s.longestIncreasingPath(v) << endl;
  return 0;
}
