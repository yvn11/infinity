#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    vector<string> fizzBuzz2(int n) {
        vector<string> ret;
        for (int i = 1, f = 0, b = 0; i < n+1; ++i) {
          ++f; ++b;
          if (f == 3 && b == 5) {
            ret.push_back("FizzBuzz");
            f = b = 0;
          } else if (f == 3) {
            ret.push_back("Fizz");
            f = 0;
          } else if (b == 5) {
            ret.push_back("Buzz");
            b = 0;
          } else {
            ret.push_back(to_string(i));
          }
        }

        return ret;
    }

    vector<string> fizzBuzz(int n) {
        vector<string> ret;
        
        for (int i = 1; i < n+1; ++i) {
            if (i%3==0 && i%5==0) {
                ret.push_back("FizzBuzz");
            } else if (i%3==0) {
                ret.push_back("Fizz");
            } else if (i%5==0) {
                ret.push_back("Buzz");
            } else {
                ret.push_back(to_string(i));
            }
        }
        
        return ret;
    }
};


int main() {
  Solution s;
  for (auto n : s.fizzBuzz(15)) {
    cout << n << ',';
  }
  cout << endl;

  for (auto n : s.fizzBuzz2(15)) {
    cout << n << ',';
  }
  cout << endl;

  return 0;
}
