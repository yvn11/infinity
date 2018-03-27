#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = 0, n2 = 0;

        if (num1 == "0" || num2 == "0")
          return "0";
        
        if (num1.length() == 0 || num2.length() == 0)
          return "0";
        
        string ret("");
        int carry = 0, res = 0;
        vector<int> res_n(num1.length()+num2.length(), 0);
        int ind_n1 = 0, ind_n2 = 0;

        for (int i = num1.length()-1; i >= 0; --i) {
          n1 = num1[i]-48;
          ind_n2 = 0;
          carry = 0;

          for (int j = num2.length()-1; j >= 0; --j) {
            n2 = num2[j]-48;
            res = n1 * n2 + carry + res_n[ind_n1+ind_n2];
            carry = res / 10;
            res_n[ind_n1+ind_n2] = res % 10;
            ind_n2++;
          }
          if (carry != 0)
            res_n[ind_n1+ind_n2] += carry;
          ind_n1++;
        }

        for (int i = res_n.size()-1; i >= 0; --i) {
          if (res_n[i] == 0 && ret.length() == 0)
            continue;
          ret += char(res_n[i]+48);
        }

        return ret.length() > 0 ? ret : "0";
    }
};

int main() {
  Solution s;
  cout << s.multiply("10", "32") << '\n';
  cout << s.multiply("9", "9") << '\n';
  cout << s.multiply("123", "321") << '\n';
  cout << s.multiply("987654321", "123456789") << '\n';
  return 0;
}
