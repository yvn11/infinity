#include <iostream>

using namespace std;

class Solution {
public:
    string reverseString(string s) {
        int i = 0, j = s.length()-1;
        while (j > i) {
            swap(s[i++], s[j--]);
        }
        
        return s;
    }
};


int main() {
  Solution s;
  cout << s.reverseString("morning") << endl;
  return 0;
}
