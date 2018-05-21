#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include "trie_node.h"

using namespace std;

class Solution {
public:
    void build_trie(TrieNode* root, vector<string>& words) {
      if (!root)
        return;
      TrieNode *p = root;

      for (auto w : words) {
        p = root;
        string pref;
        for (auto c : w) {
          pref += c;
          if (!p->next[c-'a'])
            p->next[c-'a'] = new TrieNode();
          p = p->next[c-'a'];
        }
        p->word = pref;
      }
    }
   
    int find_break(string s, TrieNode *root, int begin, unordered_set<int> &visited) {
      if (visited.find(begin) != visited.end())
        return 0;
      visited.insert(begin);

      int i = begin;
      if (i < s.length() && !root->next[s[i]-'a'])
        return 0;

      TrieNode *p = root;
      while (i < s.length()) {
        if (!p->word.empty()) {
          if (find_break(s, root, i, visited) == s.length())
            return s.length();
        }
        if (p->next[s[i]-'a']) {
          p = p->next[s[i]-'a'];
          ++i;
          continue;
        }
        return 0;
      }

      if (p->word.empty())
        return 0;
      
      return i;
    }
    
    bool trie_solution(string s, vector<string>& wordDict) {
      TrieNode* root = new TrieNode();
      unordered_set<int> visited;
      
      build_trie(root, wordDict);
      int end = find_break(s, root, 0, visited);
      return end == s.length();
    }

    bool dfs_solution(string s, vector<string>& wordDict) {
      unordered_set<string> mem(wordDict.begin(), wordDict.end());
      unordered_set<int> visited;
      queue<int> indices;
      indices.push(0);

      while (!indices.empty()) {
        int begin = indices.front();
        indices.pop();

        if (visited.find(begin) != visited.end())
          continue;
        visited.insert(begin);

        for (int i = begin; i < s.length(); ++i) {
          string sub(s.substr(begin, i-begin+1));
          if (mem.find(sub) != mem.end()) {
            indices.push(i+1);
            if (i + 1 == s.length())
              return true;
          }
        }
      }

      return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
      //return dfs_solution(s, wordDict); // 9ms
      return trie_solution(s, wordDict); // 6ms
    }
};


int main() {
  Solution s;
  //vector<string> v = {"aaaa", "aa"}; string w("catsandog");
  //vector<string> v = {"cats", "dog", "sand", "and", "cat"}; string w("aaaaaaa");
  vector<string> v = {"apple", "pen"}; string w("applepenapple");
  cout << s.wordBreak(w, v) << endl;
  return 0;
}
