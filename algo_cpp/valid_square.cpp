#include <iostream>
#include <unordered_set>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    int dist(vector<int> &p1, vector<int> &p2) {
      return pow(p1[1]-p2[1], 2)+pow(p1[0]-p2[0], 2);
    }
  
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
      unordered_set<int> mem = {
        dist(p1, p2), dist(p1, p3), dist(p1, p4), dist(p2, p3), dist(p2, p4), dist(p3, p4)
      };
      return mem.size() == 2 && (mem.find(0) == mem.end());
    }
};


int main() {
  Solution s;
  vector<vector<int>> ps = {
    {1,0},{-1,0},{0,1},{0,-1},
  };
  cout << s.validSquare(ps[0], ps[1], ps[2], ps[3]) << endl;
  return 0;
}
