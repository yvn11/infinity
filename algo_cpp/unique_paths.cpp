#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Solution {
public:
    void do_unique(int m, int n, vector<vector<int>> &mem) {
        if (m < 0 || n < 0) {
          return;
        }

        if (mem[m][n] != -1) {
            return;
        }
        
        if (m == 0 || n == 0) {
            mem[m][n] = 1;
            return;
        }
        
        this->do_unique(m-1, n, mem);
        this->do_unique(m, n-1, mem);
        mem[m][n] = mem[m-1][n]+mem[m][n-1];
    }
    
    int uniquePaths(int m, int n) {
        vector<vector<int>> mem(m, vector<int>(n, -1));
        this->do_unique(m-1, n-1, mem);
        return mem[m-1][n-1];
    }
};

int main() {
  Solution s;
  cout << s.uniquePaths(3, 7) << endl;
  return 0;
}
