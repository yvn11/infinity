#include <iostream>
#include <limits.h>
#include <math.h>

using namespace std;

class Solution {
public:
    
    bool do_is_palindrome(int x, int* y) {
        if (x >= 0 && x < 10) {
            return x == *y%10;
        }
        
        if (!this->do_is_palindrome(x/10, y)){
            return false;
        }
        *y /= 10;
        return (x%10 == *y%10);
    }

    bool isPalindrome(int x) {
        //x = abs(x);
        if (x < 0)
          return false;
        int* y = new int(x);
        return this->do_is_palindrome(x, y);
    }
};

int main() {
  Solution s;
  cout << s.isPalindrome(-INT_MAX) << '\n';
  cout << s.isPalindrome(13231) << '\n';
  return 0;
}
