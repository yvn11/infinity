#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    string frequencySort(string s) {
      unordered_map<int, vector<char>> mem;
      vector<int> freqs;

      sort(s.begin(), s.end());

      for (int i = 0; i < s.length(); ++i) {
        int freq = 1;

        while (i < s.length()-1 && s[i] == s[i+1]) {
          ++freq;
          ++i;
        }

        if (mem.find(freq) == mem.end()) 
          freqs.push_back(freq);
        mem[freq].push_back(s[i]);
      }

      string ret;
      sort(freqs.begin(), freqs.end(), greater<int>());

      for (auto i : freqs) {
        for (auto c : mem[i]) {
          for (int k = i; k > 0; --k)
            ret += c;
        }
      }

      return ret;
    }
};


int main() {
  Solution s;
  cout << s.frequencySort("aaawwooooo") << endl;
  return 0;
}

