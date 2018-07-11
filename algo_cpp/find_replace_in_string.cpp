#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
      string ret("");
      if (S.empty())
        return ret;

      int src_i = 0;
      unordered_map<int, pair<int, string>> mem;

      for (auto src : sources) {
        size_t found = 0;
        
        do {
            if (found == string::npos)
              break;
            found = (found == 0) ? S.find(src, found) : S.find(src, found+1);
            if (found != string::npos && found == indexes[src_i]) {
              mem[found] = make_pair(src.length(), targets[src_i]);
              break;
            }
        } while (found != string::npos);
        ++src_i;
      }

      int i = 0; 
      while (i < S.length()) {
        if (mem.find(i) == mem.end()) {
          ret += S[i];
          ++i;
        } else {
          ret += mem[i].second;
          i += mem[i].first;
        }
      }

      return ret;
    }
};


int main() {
  Solution s;
  string S("wreorttvosuidhrxvmvo");
  vector<int> indexes = {14,12,10,5,0,18};
  vector<string> sources = {"rxv","dh","ui","ttv","wreor","vo"};
  vector<string> targets = {"frs","c","ql","qpir","gwbeve","n"};

  cout << s.findReplaceString(S, indexes, sources, targets) << endl;

  return 0;
}
