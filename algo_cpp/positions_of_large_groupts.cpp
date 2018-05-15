#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
      vector<vector<int>> ret;
      int i = 0, j = i;
      while (i < S.length()) {
        if (S[i] == S[i+1]) {
          ++i; continue;
        }
        
        if (i-j+1 >= 3) {
          ret.push_back(vector<int>{j, i});
        }
        j = ++i;
      }
      return ret;
    }
};


int main() {
  Solution s;
  for (auto v : s.largeGroupPositions("ddddks2222ccccddac")) {
    for_each(v.begin(), v.end(), [&](auto p){cout << p << ',';});
    cout << endl;
  }
  return 0;
}
