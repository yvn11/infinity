#include <iostream>
#include <algorithm>

using namespace std;

int lengthOfLongestSubstring(string s) {
        if (s.length() == 0)
            return 0;

        int mem[128];
        int cur = 1, ret = 1, prev;
        int c = s[0];

        for (int i = 1; i< 128;i++) {
          mem[i] = -1;
        }
        mem[c] = 0;

        for (int i = 1; i < s.length(); i++) {
            c = s[i];
            prev = mem[c];
            
            if (prev == -1 || i - cur > prev) {
                cur += 1;
            } else {
                ret = max(ret, cur);
                cur = i - prev;
            }
            mem[c] = i;
        }
        
        ret = max(ret, cur);
        return ret;
    }

int main() {
  cout << lengthOfLongestSubstring("au") << '\n';
  return 0;
}
