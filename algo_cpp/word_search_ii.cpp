#include <iostream>
#include <vector>
#include <algorithm>
#include "trie_node.h"

using namespace std;


class Solution {
public:
    void findWords(vector<vector<char>> &board, int m, int n,
                            TrieNode *root, vector<string> &ret) {

      char c = board[m][n];
      if (c == '.'|| !(root->next[c-'a']))
        return;
      
      root = root->next[c-'a'];
      if (!root->word.empty()) {
        ret.push_back(root->word);
        root->word.clear();
      }

      board[m][n] = '.';

      if (m > 0)
        findWords(board, m-1, n, root, ret);
      if (m+1 < board.size())
        findWords(board, m+1, n, root, ret);
      if (n > 0)
        findWords(board, m, n-1, root, ret);
      if (n+1 < board[0].size())
        findWords(board, m, n+1, root, ret);

      board[m][n] = c;
    }
  
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
      vector<string> ret;
      
      if (words.empty() || board.empty())
        return ret;
    
      TrieNode *root = new TrieNode(), *p = root;
      for_each(words.begin(), words.end(), [&](auto w) {
        p = root;
        string pref;
        for_each(w.begin(), w.end(), [&](auto c) {
          pref += c;
          if (!p->next[c-'a'])
            p->next[c-'a'] = new TrieNode();
          p = p->next[c-'a'];
        });
        p->word = pref;
      });

      for (int i = 0; i < board.size(); ++i)
        for (int j = 0; j < board[0].size(); ++j) {
          findWords(board, i, j, root, ret);
        }
      
      return ret;
    }
};


int main() {
  Solution s;
  vector<vector<char>> board = {
    //{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}
    //{'a','b'},{'c','d'}
    {'a','b'},{'a','a'}
    //{'s','e','e','n','e','w'},{'t','m','r','i','v','a'},{'o','b','s','i','b','d'},{'w','m','y','s','e','n'},{'l','t','s','n','s','a'},{'i','e','z','l','g','n'}
  };

  vector<string> words = {
    //"oath","pea","eat","rain",
    //"ab","cb","ad","bd","ac","ca","da","bc","db","adcb","dabc","abb","acb"
    "aba","baa","bab","aaab","aaa","aaaa","aaba"
  };

  for (auto w : s.findWords(board, words))
    cout << w << ',';
  cout << endl;
  return 0;
}
