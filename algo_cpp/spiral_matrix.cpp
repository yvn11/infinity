#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int m = matrix.size();
        int i = 0, j = 0, k = 0;

        if (m == 0)
          return ret;

        int n = matrix[0].size();
        
        while (i < m && j < n) {
            for (k = j; k < n; ++k) {
                if (matrix[i][k] != INT_MAX) {
                  ret.push_back(matrix[i][k]);
                  matrix[i][k] = INT_MAX;
                }
            }
            i++;

            for (k = i; k < m; ++k){
                if (matrix[k][n-1] != INT_MAX) {
                  ret.push_back(matrix[k][n-1]);
                  matrix[k][n-1] = INT_MAX;
                }
            }
            n--;
            
            if (j < n) {
                for (k = n-1; k >= j; --k){
                    if (matrix[m-1][k] != INT_MAX) {
                      ret.push_back(matrix[m-1][k]);
                      matrix[m-1][k] = INT_MAX;
                    }
                }
                m--;
            }

            if (i < m) {
                for (k = m-1; k >= i; --k){
                    if (matrix[k][j] != INT_MAX) {
                      ret.push_back(matrix[k][j]);
                      matrix[k][j] = INT_MAX;
                    }
                }
                j++;
            }
        }
        return ret;
    }
};


int main() {
    Solution s;
    vector<vector<int>> v = {
        {1,2,3,11},
        {4,5,6,12},
        {7,8,9,13},
        {14,15,16,17},
    };

    v = {
      {2,3}};

    for (auto g : s.spiralOrder(v)) {
        cout << g << ',';
    }
    cout << endl;
    return 0;
}
