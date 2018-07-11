#include <iostream>
#include <vector>
#include <limits.h>
#include <unordered_map>

using namespace std;


class Solution {
public:
    
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        vector<vector<int>> mem(m+1, vector<int>(n+1, 0));

        for (int i = 1; i <= m; ++i) {
          mem[i][0] = mem[i-1][0] + s1[i-1];
        }

        for (int i = 1; i <= n; ++i) {
          mem[0][i] = mem[0][i-1] + s2[i-1];
        }

        char c1, c2;

        for (int i = 1; i <= m; ++i) {
          for (int j = 1; j <= n; ++j) {
            c1 = s1[i-1]; c2 = s2[j-1];
            int t = (c1 == c2) ? 0 : c1+c2;
            mem[i][j] = min(mem[i][j-1] + c2, mem[i-1][j] + c1);
            mem[i][j] = min(mem[i][j], mem[i-1][j-1] + t);
          }
        }

        return mem[m][n];
    }
};

int main() {
  Solution s;
  cout << s.minimumDeleteSum("delete", "leet") << endl;
  cout << s.minimumDeleteSum("sea", "eat") << endl;
  return 0;
}
