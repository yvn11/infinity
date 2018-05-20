#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <math.h>

using namespace std;

class Solution {
public:
  
    double new21Game(int N, int K, int W) {
      if (K==0) return 1.0;
      vector<double> mem(N+1, 1.0);
      double ret = 0.0, sum = mem[0];

      for (int i = 1; i <= N; ++i) {
        mem[i] = sum/W;
        if (i < K) sum += mem[i];
        else ret += mem[i];
        if (i-W >= 0 && K > i-W)
          sum -= mem[i-W];
      }

      return ret;
    }
};

int main() {
  Solution s;
  cout << s.new21Game(21, 17, 10) << endl;
  cout << s.new21Game(6, 1, 10) << endl;
  cout << s.new21Game(10, 1, 10) << endl;
  return 0;
}
