#include <iostream>
#include <vector>

using namespace std;


class Solution {
  public:
    int lcs(string a, string b) {
      vector<vector<int>> mem(a.size()+1, 
          vector<int>(b.size()+1, 0));
      int ret = 0;

      for (int i = 1; i <= a.length(); ++i) {
        for (int j = 1; j <= b.length(); ++j) {
          if (a[i-1] == b[j-1]) {
            mem[i][j] = mem[i-1][j-1]+1;
            ret = max(ret, mem[i][j]);
          } else {
            mem[i][j] = 0;
          }
        }
      }

      return ret;
    }
};



int main() {
  Solution s;
  cout << s.lcs("iijjsldoaaagbid", "aaagbidkcccaiij") << endl;;
  return 0;
}
