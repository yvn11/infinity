#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
      int n = A.size();
      int i = 0;
      while (i < n) {
        int j = 0, k = n-1;
        while (j <= k) {
          A[i][j] ^= 1;
          if (j != k) {
            A[i][k] ^= 1;
            swap(A[i][j], A[i][k]);
          }
          ++j; --k;
        }
        ++i;
      }
      return A;
    }
};

int main() {
  Solution s;
  vector<vector<int>> v = {
    {1,0,1}, {0,0,1},{1,1,1}
  };
  for (auto m : s.flipAndInvertImage(v)) {
    for (auto n : m) {
      cout << n << ',';
    } 
    cout << endl;
  }

  return 0;
}
