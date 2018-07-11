#include <iostream>

using namespace std;


class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
            return 0;
        
        int ret = -1;
        int i = 0;

        while (i + needle.length() -1 < haystack.length()) {
            if (haystack[i]==needle[0]){
                int j = 0;
                while (j < needle.length() && haystack[i+j]==needle[j]) {
                    ++j;
                }
            
            if (j == needle.length()) {
                ret = i;
                break;
            }
          }
          ++i;
        }
        return ret;
    }
};


int main() {
  Solution s;
  cout << s.strStr("sissssimsi", "sim") << endl;
  return 0;
}
