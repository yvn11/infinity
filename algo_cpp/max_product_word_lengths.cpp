#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int maxProduct(vector<string>& words) {
      int ret = 0;
      vector<int> mem(words.size(), 0);
      
      for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < words[i].length(); ++j) {
          mem[i] |= (1 << int(words[i][j]-'a'));
        }
      }

      for (int i = 0; i < words.size(); ++i) {
        for (int j = i+1; j < words.size(); ++j) {
          if (!(mem[i] & mem[j])) {
            ret = max(ret, int(words[i].length()*words[j].length()));
          }
        }
      }

      return ret;
    }
};

int main() {
  Solution s;
  vector<string> v = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  cout << s.maxProduct(v) << endl;
  return 0;
}
