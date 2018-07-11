#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;


class Solution {
public:

    bool stream_solution(string pattern, string str) {
      if (pattern.empty() && !str.empty())
        return false;
      if (!pattern.empty() && str.empty())
        return false;
      
      int count = 0, begin = 0;
      unordered_map<char, string> mem;
      unordered_map<string, char> mem2;
      
      istringstream is(str);
      string sub;

      while (is >> sub) {
        if (mem.find(pattern[count]) == mem.end()) {
          if (mem2.find(sub) == mem2.end()) {
            mem[pattern[count]] = sub;
            mem2[sub] = pattern[count];
            ++count;
          } else {
            return false;
            }
        } else if (mem[pattern[count++]] != sub)
          return false;
      }
    }

    bool wordPattern(string pattern, string str) {
      if (pattern.empty() && !str.empty())
        return false;
      if (!pattern.empty() && str.empty())
        return false;
      
      int count = 0, begin = 0;
      unordered_map<char, string> mem;
      unordered_map<string, char> mem2;
      
      for (int i = 0; i < str.length(); ++i) {
        if (str[i] != ' ' && i != str.length()-1)
          continue;
        if (i == str.length()-1)
          ++i;
        string sub(str.substr(begin, i-begin));
        if (mem.find(pattern[count]) == mem.end()) {
          if (mem2.find(sub) == mem2.end()) {
            mem[pattern[count]] = sub;
            mem2[sub] = pattern[count];
            ++count;
          } else {
            return false;
          }
        } else if (mem[pattern[count++]] != sub)
            return false;
        begin = i+1;
      }

      return count == pattern.length();
    }
};


int main() {
  Solution s;
  cout << s.wordPattern("abba", "dog cat cat fish") << endl;
  cout << s.wordPattern("abba", "dog cat cat dog") << endl;
  return 0;
}
