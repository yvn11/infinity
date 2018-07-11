#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int climbStairs(int n) {
        vector<int> mem(n);
        mem[0] = 1;
        mem[1] = 2;

        for (int i = 2; i < n; ++i) {
            mem[i] = mem[i-1] + mem[i-2];    
        }
        
        return mem[n-1];
    }
};


int main() {
  Solution s;
  cout << s.climbStairs(1) << endl;
  cout << s.climbStairs(2) << endl;
  cout << s.climbStairs(3) << endl;
  cout << s.climbStairs(4) << endl;
  cout << s.climbStairs(5) << endl;
  return 0;
}
