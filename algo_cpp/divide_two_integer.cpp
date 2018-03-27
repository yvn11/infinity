#include <iostream>
#include <limits.h>

using namespace std;


class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0) {
            return INT_MAX;
        }
         
        if (dividend < INT_MIN || dividend > INT_MAX) {
          return INT_MAX;
        }

        if (dividend == INT_MIN && divisor < 0) {
          return INT_MAX;
        }

        int sign = ((dividend < 0)^(divisor < 0)) ? -1 : 1;
        //dividend = abs(dividend);
        //divisor = abs(divisor);

        if (abs(dividend) == abs(divisor)) {
          return 1*sign;
        }

        if (abs(dividend) == 1) {
          return dividend*sign;
        }

        int ret = 0;
        
        while (abs(dividend) >= abs(divisor)) {
            dividend = dividend > 0 ? dividend - divisor : dividend + divisor;
            cout << dividend << ' ';
            ret++;
        }
        
        return sign > 0 ? ret : 0-ret;
    }
};


int main() {
  Solution s;
  cout << s.divide(15, 3) << endl;
  cout << s.divide(-2147483648, -1) << endl;
  cout << s.divide(-2147483648, 2) << endl;
  cout << s.divide(-1, 1) << endl;
//  cout << s.divide(2147483647, 2) << endl;
  cout << s.divide(1, -1) << endl;
  cout << s.divide(2, 2) << endl;
  return 0;
}
