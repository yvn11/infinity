#include <iostream>
#include <limits.h>
#include <math.h>
#include <algorithm>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        if (str.length() == 0) {
            return 0;
        }

        if (str.length() == 1) {
            if (str[0] < '9' && str[0] > '0')
                return str[0]-48;
            return 0;
        }

        int sign = -1;
        int ret = 0;
        int i = 0;

        while (str[i] == ' ') i++;

        for (; i < str.length(); ++i) {
            char c = str[i];

            if (c == '-') {
                if (sign != -1) {
                    return 0;
                }
                sign = 0;
                continue;
            }

            if (c == '+') {
                if (sign != -1) {
                    return 0;
                }
                sign = 1;
                continue;
            }

            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || ' ') {
                break;
            }

            if ((c > '9' || c < '0')) {
                return 0;
            }

            c -= 48;

            if (ret > (INT_MAX)/10) {
                if (sign == 0)
                    return INT_MIN;
                return INT_MAX;
            }

            if (ret < (INT_MIN)/10) {
                if (sign != 0)
                    return INT_MAX;
                return INT_MIN;
            }

            ret = ret*10 + c;
        }
        if (sign != 0 && ret - INT_MAX > 0) {
            return INT_MAX;
        }

        if (sign == 0 && ret - INT_MAX > 0) {
            return INT_MIN;
        }
        return sign != 0 ? ret : 0-ret;
    }
};


int main() {
  Solution s;
  cout << s.myAtoi("-2147483647") << '\n';
  cout << s.myAtoi("2147483648") << '\n';
  cout << s.myAtoi("-2147483649") << '\n';
  return 0;
}
