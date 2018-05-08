#include <iostream>

using namespace std;

class Solution {
public:
    bool rotateString(string A, string B) {
      if (B.length() != A.length())
        return false;

      A += A;
      
      for (int i = 0; i <= A.length()-B.length(); ++i) {
        if (B == A.substr(i, B.length()))
          return true;
      }
      return false;
    }
};

int main() {
  Solution s;
  cout << s.rotateString("abcde", "cdeab") << endl;
  cout << s.rotateString("a", "") << endl;
  cout << s.rotateString("vcuszhlbtpmksjleuchmjffufrwpiddgyynfujnqblngzoogzg",
"fufrwpiddgyynfujnqblngzoogzgvcuszhlbtpmksjleuchmjf") << endl;
  cout << s.rotateString("", "") << endl;
  return 0;
}
