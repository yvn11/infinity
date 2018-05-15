#include <iostream>

using namespace std;


class Solution {
public:
    void reverseWords(string &s) {
        for (int i = 0, j = s.length()-1; i < j; ++i, --j)
            swap(s[i], s[j]);

        for (int i = 0; i < s.length(); ++i) {
            auto j = s.find(" ", i), c = j;
            if (i == j) {
              i = c;
              continue;
            }

            if (j == string::npos) {
              c = j = s.length()-1;
            } else {
              --j;
            }

            while (i < j)
              swap(s[i++], s[j--]);
            i = c;
        }        
    }
};


int main() {
  Solution s;
  string str("quantum physics is so much fun");
  s.reverseWords(str);
  cout << str << endl;
  return 0;
}
