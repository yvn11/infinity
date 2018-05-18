#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
      vector<string> table = {".-","-...","-.-.","-..",".","..-.",
                              "--.","....","..",".---","-.-",".-..",
                              "--","-.","---",".--.","--.-",".-.",
                              "...","-","..-","...-",".--","-..-","-.--","--.."};
      unordered_set<string> mem;
      
      for (auto w : words) {
        string c;
        for (auto i : w)
          c += table[i-'a'];
        mem.insert(c);
      }
      return mem.size();
    }
};


int main() {
  Solution s;
  vector<string> v = {"goodday", "hollween"};
  cout << s.uniqueMorseRepresentations(v) << endl;
  return 0;
}
