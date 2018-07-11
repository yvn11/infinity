#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits.h>

using namespace std;


class Solution {
public:
    int reverse(int x) {
        if (abs(x) > INT_MAX) {
            return 0;
        }
        
        bool sign = x > 0 ? true: false;
        int ret = 0;
        int r = 0;

        while (abs(x) > 0) {
            r = x % 10;
            x = x / 10;
            if (ret > INT_MAX/10 || ret < INT_MIN/10) {
              return 0;
            }
            ret = ret*10 + r;
        }
        
        return sign ? ret : 0-abs(ret);
    }
};

int main() {
  Solution s;
  cout << s.reverse(-123) << '\n';
  cout << s.reverse(1534236469) << '\n';
  return 0;
}
