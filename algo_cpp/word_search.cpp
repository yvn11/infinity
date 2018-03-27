#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool do_exist(vector<vector<char>> &board, string word,
                 int m, int n, int ind, vector<vector<bool>> mem){
        if (mem[m][n]) {
          return false;
        }

        mem[m][n] = true;

        if (board[m][n] != word[ind])
          return false;

        if (ind = word.length()) {
            return true;
        }

        if (ind+1 >= word.length())
            return false;
        
        if (m < board.size()-1 && word[ind+1] == board[m+1][n])
          if (this->do_exist(board, word, m+1, n, ind+1, mem))
            return true;
        if (n < board[0].size()-1 && word[ind+1] == board[m][n+1])
          if (this->do_exist(board, word, m, n+1, ind+1, mem))
            return true;
        if (m > 0 && word[ind+1] == board[m-1][n])
          if (this->do_exist(board, word, m-1, n, ind+1, mem))
            return true;
        if (n > 0 && word[ind+1] == board[m][n-1])
          if (this->do_exist(board, word, m, n-1, ind+1, mem))
            return true;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                vector<vector<bool>> mem(m, vector<bool>(n, false));
                bool ret = this->do_exist(board, word, i, j, 0, mem);
                if (ret) 
                  return true;
            }
        }
        return false;
    }
};

int main() {
  Solution s;
  vector<vector<char>> v = {
    {'A','B','C','E'},
    {'S','F','E','S'},
    {'A','D','E','E'}
  };
  string w("ABCESEEEFS");
  cout << s.exist(v, w) << '\n';
  return 0;
}
