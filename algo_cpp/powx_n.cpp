#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    void do_pow(double x, int n, unordered_map<int, double> &mem) {
        if (n == 0) {
            mem[n] = n >= 0 ? 1.0 : -1.0;
            return;
        }

        if (abs(n) == 1) {
            mem[n] = n > 0 ? x : 1.0/x;
            return;
        }

        this->do_pow(x, n/2, mem);

        if (n % 2 == 0) {
            mem[n] = mem[n/2]*mem[n/2];
        } else {
            mem[n] = n > 0 ? mem[n/2]*mem[n/2]*x : mem[n/2]*mem[n/2]/x;
        }

    }
    double myPow(double x, int n) {
        unordered_map<int, double> mem;
        this->do_pow(x, n, mem);
        return mem[n];
    }
};


int main() {
  Solution s;
  cout << s.myPow(2, -3) << '\n';
  cout << s.myPow(2, 10) << '\n';
  cout << s.myPow(-0.448, 0) << '\n';
  cout << s.myPow(22.14659, -2) << '\n';
  return 0;
}
