#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <numeric>

using namespace std;

int mod = pow(10, 9)+7;

class Solution {
public:
    int linear(string S) {
      int ret = 0;
      unordered_map<char, list<int>> count;

      unordered_set<char> mem, dup;
      for (int i = 0; i < S.length(); ++i) {
        count[S[i]].push_back(i);
        if (mem.find(S[i]) != mem.end()) {
          mem.erase(S[i]);
          dup.insert(S[i]);
        } else if (dup.find(S[i]) == mem.end()) {
          mem.insert(S[i]);
        }
        ret += mem.size();
        ret %= mod;
      }

      int cur = ret;
      for (int i = 1; i < S.length(); ++i) {
        list<int> &chain = count[S[i-1]];
        chain.pop_front();

        if (chain.empty()) {
          cur = max(0, int(cur-(S.length()-i)-1));
        } else {
          if (chain.size() == 1) {
            cur += S.length()-chain.front() -1;
          } else {// (chain.size() > 1) 
            cur += *next(chain.begin())-chain.front()-1;
          }
          cur = max(0, cur-(chain.front() - i));
        }

        ret += cur;
        ret %= mod;
      }

      return ret;
    }

    int n2(string S) {
        int ret = 0;

        for (int k = 0; k < S.length(); ++k) {
          unordered_set<char> mem, dup;
          for (int i = k; i < S.length(); ++i) {
            if (mem.find(S[i]) != mem.end()) {
              mem.erase(S[i]);
              dup.insert(S[i]);
            } else if (dup.find(S[i]) == mem.end()) {
              mem.insert(S[i]);
            }
            ret += mem.size();
            ret %= mod;
          }
        }


        return ret;
    }

    int uniqueLetterString(string S) {
      return linear(S);
    }
};


int main() {
  Solution s;

  cout << s.uniqueLetterString("ABA") << endl;
  cout << s.uniqueLetterString("ABC") << endl;
  cout << s.uniqueLetterString("ABDDEAA") << endl;
  cout << s.uniqueLetterString("ABDDEA") << endl;
  cout << s.uniqueLetterString("ABABAB") << endl;
  cout << s.uniqueLetterString("AAA") << endl;
  return 0;
}
