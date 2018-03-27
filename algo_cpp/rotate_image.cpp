#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        vector<int> mem(matrix[0]);
        int n = matrix.size();
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; i+j != n-1; ++j) {
                swap(matrix[i][j], matrix[n-1-j][n-1-i]);
            }
        }
        
        for (int i = 0; i < n/2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(matrix[i][j], matrix[n-1-i][j]);
            }
        }
    }
};

int main() {
  Solution s;
  vector<vector<int>> v = {
    {1,2,3},
    {4,5,6},
    {7,8,9},
  };
  s.rotate(v);

  for (auto vn : v) {
    for (auto n : vn) {
      cout << n << ',';
    }
    cout << endl;
  }
  return 0;
}
