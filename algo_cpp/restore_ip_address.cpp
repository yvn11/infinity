#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool is_valid(string buf) {
        if (stoi(buf) > 255)
          return false;
        if (buf[0] == '0' && buf.length() > 1)
          return false;
        return true;
    }

    void do_restore(string s, vector<string> &mem, 
                    int last, string cur, int dot_cnt) {
      if (dot_cnt == 0) {
        if (s.length()-last > 3 || s.length()-last == 0)
          return;

        string buf = s.substr(last, s.length()-last);
        if (!this->is_valid(buf))
          return;

        cur += buf;
        if (cur[cur.length()-1] == '.')
          return;

        if (cur.length() == s.length()+3) {
          mem.push_back(cur);
          return;
        }
      }

      if (s.length() == last)
        return;

      for (int i = 4; i > 0; --i) {
        string buf = s.substr(last, i);
        if (!this->is_valid(buf) || i > s.length()-last)
          continue;
        string next = cur + buf + ".";
        this->do_restore(s, mem, last+i, next, dot_cnt-1);
      }
    }
    
    vector<string> restoreIpAddresses(string s) {
        vector<string> mem;
        this->do_restore(s, mem, 0, "", 3);
        return mem;
    }
};

int main() {
    Solution s;

    for (auto g : s.restoreIpAddresses("010010")) {
        cout << g << ',';
    }
    cout << endl;
    return 0;
}
