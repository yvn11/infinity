#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    string pushDominoes(string dominoes) {
      int n = dominoes.size();
      vector<char> mem(dominoes.begin(), dominoes.end());
      mem.insert(mem.begin(), '.'); mem.push_back('.');
      string ret;

      for (int i = 1; i < n+1; ++i) {
        if (mem[i] != '.')
          continue;
        int j = i-1, k = i;

        while (k < n+1 && mem[k] == '.') ++k;

        i = k;
        if (k < n+1 && mem[j] == '.') 
          while (j < k && mem[k] == 'L') mem[--k] = 'L';
        else if (j >= 0 && mem[k] == '.') 
          while (j < k && mem[j] == 'R') mem[++j] = 'R';
        else if ((k-j+1) % 2 != 0) {
          while (j < k) {
            if (mem[k] != 'L' && mem[j] != 'R')
              break;
            if (mem[k] == 'L' && mem[k-2] != 'R') mem[--k] = 'L';
            if (mem[j] == 'R' && mem[j+2] != 'L') mem[++j] = 'R';
            if (j + 2 >= k) {
              if (mem[j] == mem[k])
                mem[k-1] = mem[k];
              break;
            }
          }
        } else {
          while (j + 1 < k) {
            if (mem[k] != 'L' && mem[j] != 'R')
              break;
            if (mem[k] == 'L') mem[--k] = 'L';
            if (mem[j] == 'R') mem[++j] = 'R';
          }
        }
      }

      for (int i = 1; i < n+1; ++i)
        ret += mem[i];

      return ret;
    }
};

int main() {
  Solution s;
  cout << s.pushDominoes(".L.R...LR..L..") << endl;
  cout << s.pushDominoes("R.R.L") << endl;
  cout << s.pushDominoes("RRL") << endl;
  cout << s.pushDominoes(".......L.L") << endl;
  cout << s.pushDominoes("R.......L.R.........") << endl;
  cout << s.pushDominoes("L.L...L.L.LL.L..L...") << endl;
  return 0;
}
