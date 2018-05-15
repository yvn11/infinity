#include <iostream>

using namespace std;

class Solution {
public:
    /*Sum a and b without "+" or "-"*/
    int getSum(int a, int b) {
      int s = __builtin_popcount(a) > __builtin_popcount(b) ? b : a;
      int o = s == a ? b : a;
      return s == 0 ? o : getSum(s^o, (s&o) << 1);
    }
};

int main() {
  Solution s;
  cout << s.getSum(5, 8) << endl;
  return 0;
}
