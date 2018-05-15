#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
      vector<vector<string>> ret;
      unordered_map<string, vector<string>> mem;

      for (auto p : paths) {
        int space = p.find(' '), lb = 0, rb = 0;
        string base = p.substr(0, space);

        while (space >= 0) {
          lb = p.find('(', space+1);
          rb = p.find(')', lb);
          string file = p.substr(space+1, lb-space-1);
          string content = p.substr(lb+1, rb-lb-1);
          mem[content].push_back(base+"/"+file);
          space = p.find(' ', space+1);
        }
      }

      for (auto it : mem) {
        if (it.second.size() < 2)
          continue;
        ret.push_back(it.second);
      }
      return ret;  
    }
};


int main() {
  Solution s;
  vector<string> v = {"root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"};
  for (auto l : s.findDuplicate(v)) {
    for (auto n : l) {
      cout << n << ',';
    }
    cout << endl;
  }
  return 0;
}

