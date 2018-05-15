#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Solution {
public:
    int search_row(vector<vector<int>>& matrix, int target,
        int begin, int end) {
      if (end-begin < 0)
        return -1;

      if (end-begin == 0)
        return begin;

      int m = matrix.size(), n = matrix[0].size();
      int mid = (begin+end)/2;

      if (matrix[mid][0] <= target && matrix[mid][n-1] >= target)
        return mid;

      if (matrix[mid][0] < target)
        return search_row(matrix, target, mid+1, end);
      return search_row(matrix, target, begin, mid);
    }

    bool search_col(vector<vector<int>>& matrix, int target,
        int begin, int end, int i) {
      if (end-begin < 0)
        return false;

      if (end-begin == 0)
        return matrix[i][begin] == target;

      int m = matrix.size(), n = matrix[0].size();
      int mid = (begin+end)/2;
     
      if (matrix[i][mid] == target)
        return true;

      if (matrix[i][mid] < target)
        return search_col(matrix, target, mid+1, end, i);
      return search_col(matrix, target, begin, mid, i);
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
      if (matrix.empty() || matrix[0].empty())
        return false;

      int i = this->search_row(matrix, target, 0, matrix.size()-1);
      if (i != -1)
        return this->search_col(matrix, target, 0, matrix[0].size()-1, i);
      return false;
    }
};


int main() {
  Solution s;
  vector<vector<int>> v = {
  {1,  3,}//  5,  7},
//  {10, 11, 16, 20},
//  {23, 30, 34, 50}
  };
  int t = 3;
  cout << s.searchMatrix(v, t) << endl;
  return 0;
}
