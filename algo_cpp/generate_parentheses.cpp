#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
      set<string> mem;
      this->do_generate(mem, "", n, n);
      return vector<string>(mem.begin(), mem.end());
    }

    void do_generate(set<string> &mem, string s, int left, int right) {
        if (left > right) {
          return;
        }

        if (left == 0 && right == 0) {
          mem.insert(s);
          return;
        }

        if (left > 0) {
          this->do_generate(mem, s+'(', left-1, right);
        }

        if (right > 0) {
          this->do_generate(mem, s+')', left, right-1);
        }
    }
};


int main() {
  Solution s;
  vector<string> ret = s.generateParenthesis(5);
  for (auto s : ret) {
    cout << s << ',';
  }
  cout << endl;
  cout << ret.size() << endl;
  return 0;
}
