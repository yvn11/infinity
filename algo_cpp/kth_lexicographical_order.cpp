#include <iostream>
#include <queue>

using namespace std;


class Solution {
public:
    int findKthNumber(int n, int k) {
        for (int i = 1; i <= n; ++i) {
          if (--k == 0)
            return i;

          for (int base=10*i, j = 0; base <= n && j < 10 && k > 0; ++j, ++base) {
            if (--k == 0)
              return base;
          }
        }
        return 0;
    }
};


int main() {
  Solution s;
  cout << s.findKthNumber(150, 15) << endl;
  cout << s.findKthNumber(13, 2) << endl;
  cout << s.findKthNumber(2, 2) << endl;
  cout << s.findKthNumber(100, 10) << endl;
  cout << s.findKthNumber(1, 1) << endl;
  return 0;
}
