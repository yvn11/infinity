#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool valid(vector<string> &board, int i, int j, int n) {
      for (int k = 0; k < j; ++k)
        if (board[i][k] == 'Q')
          return false;

      for (int k = i, g = j; k >= 0 && g >= 0; --k, --g)
        if (board[k][g] == 'Q')
          return false;

      for (int k = i, g = j; k < n && g >= 0; ++k, --g)
        if (board[k][g] == 'Q')
          return false;

      return true;
    }

    bool put_queen(vector<string> &board, int j, int n,
                  vector<vector<string>> &boards) {
      if (j >= n)
        return true;

      for (int i = 0; i < n; ++i) {
        if (!valid(board, i, j, n)) 
          continue;

        board[i][j] = 'Q';
        if (put_queen(board, j+1, n, boards)) {
          boards.push_back(board);
        }
        board[i][j] = '.';
      }

      return false;
    }
  
    vector<vector<string>> solveNQueens(int n) {
      vector<vector<string>> ret;
      
      vector<string> board(n, string(n, '.'));
      put_queen(board, 0, n, ret);
      
      return ret;
    }
};

int main() {
  Solution s;
  auto res = s.solveNQueens(4);
  for (auto v : res) {
    for (auto n : v) cout << n << endl;
    cout << "==========" << endl;
  }
  return 0;
}
