#include <iostream>
#include <math.h>

using namespace std;

class Solution {
public:
    bool loop(int n) {
      while (n % 3 == 0)
        n /= 3;
      return n == 1;
    }

    bool isPowerOfThree(int n) {
        int ma = pow(3, (int)(log(0x7fffffff)/log(3)));
        return n > 0 && (ma % n==0);
    }
};


int main() {
  Solution s;
  cout << s.loop(128) << endl;
  cout << s.isPowerOfThree(128) << endl;
  cout << s.loop(81) << endl;
  cout << s.isPowerOfThree(81) << endl;
  return 0;
}
