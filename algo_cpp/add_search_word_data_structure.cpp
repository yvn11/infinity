#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
  vector<TrieNode*> next;
  string word;
  
  TrieNode() {
    next.resize(26, nullptr);
  }
};


class WordDictionary {
    TrieNode* root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
      TrieNode *p = root;
      string pref;

      for (auto c : word) {
        pref += c;
        if (p->next[c-'a'] == nullptr) {
          p->next[c-'a'] = new TrieNode();
        }
        p = p->next[c-'a'];
      }
      p->word = pref;
    }

    bool do_search(string word, int i, TrieNode *p) {
      if (!p || i > word.length())
          return false;

      if (i == word.length())
        return !(p->word).empty();

      if (word[i] != '.') {
        return p->next[word[i]-'a'] && do_search(word, i+1, p->next[word[i]-'a']);
      } else {
        for (int c = 0; c < (p->next).size(); ++c) {
          if (p->next[c] && do_search(word, i+1, p->next[c]))
            return true;
        }
      }
      return false;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
      return do_search(word, 0, root);
    }
};


int main() {
  WordDictionary d;
  //d.addWord("hello");
  //d.addWord("wonderful");
  cout << d.search("good") << endl;
  cout << d.search("hello") << endl;
  cout << d.search("he.lo") << endl;
  cout << d.search("he.o") << endl;
  d.addWord("a");
  d.addWord("a");
  cout << d.search(".") << endl;
  cout << d.search("a") << endl;
  cout << d.search("aa") << endl;
  cout << d.search("a") << endl;
  cout << d.search(".a") << endl;
  cout << d.search("a.") << endl;
  return 0;
}
