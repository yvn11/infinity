#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:

    bool find_word(vector<vector<char>>& board, string word,
                   int ind, int m, int n) {
      if (board[m][n] == '.')
        return false;
      char c = board[m][n];

      if (word[ind] != c)
        return false;

      if (ind == word.length()-1)
        return true;

      board[m][n] = '.';

      if (m > 0)
        if (find_word(board, word, ind+1, m-1, n)) return true;
      if (m+1 < board.size())
        if (find_word(board, word, ind+1, m+1, n)) return true;
      if (n > 0)
        if (find_word(board, word, ind+1, m, n-1)) return true;
      if (n+1 < board[0].size())
        if(find_word(board, word, ind+1, m, n+1)) return true;

      board[m][n] = c;

      return false;
    }

    bool exist(vector<vector<char>>& board, string word) {

      for (int i = 0; i < board.size(); ++i)
        for (int j = 0; j < board[0].size(); ++j) {
          if (find_word(board, word, 0, i, j))
            return true;
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
