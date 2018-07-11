#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int compress(vector<char>& chars) {
        if (chars.empty())
          return 0;
      
        int i = 1, j = 0, k = 0;
        while (i <= chars.size()) {
          if (i < chars.size() && chars[i] == chars[i-1]) {
            ++i;
            continue;
          }
          
          if (i-k == 1) {
            chars[j++] = chars[k];
            k = i++;
            continue;
          }
          
          string l(to_string(i-k));
          chars[j++] = chars[k];

          for (auto c : l) {
            chars[j++] = c;
          }
          k = i++;
        }

        return j;
    }
};


int main() {
  Solution s;
  vector<char> v = {'d','a','c'};
  //{'a','b','b','b','c','c','c','c','c','c','c','c','c','c','c','c','c','c','d','d','d'};
  int l = s.compress(v);
  cout << "len:" << l << endl;
  for (auto it : v) {
    cout << it << ',';
    if (--l == 0) break;
  }
  cout << endl;
  return 0;
}
