#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (!s.length())
          return 0;

        if (s.length() == 1)
          if (s[0] == '0')
            return 0;
          else
            return 1;

        vector<int> mem(s.length()+1, 0);
        mem[0] = 1;
        mem[1] = 1;

        for (int i = 2; i <= s.length(); ++i) {
          if (s[i-1] > '0')
            mem[i] = mem[i-1];
          if (s[i-2] == '1' || (s[i-2] == '2' && s[i-1] < '7'))
            mem[i] += mem[i-2];
        }

        return mem[s.length()];
    }
};

int main() {
  Solution s;
  cout << s.numDecodings("1315171") << endl;
  cout << s.numDecodings("0") << endl;
  cout << s.numDecodings("10") << endl;
  cout << s.numDecodings("26") << endl;
  return 0;
}

