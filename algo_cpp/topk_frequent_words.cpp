#include <unordered_map>
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct compare {
  bool operator()(pair<string, int> a, pair<string, int> b) const {
     if (a.second == b.second) {
       return a.first > b.first;
     }
     return a.second < b.second;
  }  
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> count;
        for (auto s : words)
            count[s]++;
        
        priority_queue<pair<string, int>, 
            vector<pair<string, int>>, compare> mem(
                count.begin(), count.end());
        
        vector<string> ret;
        while (k-- > 0 && mem.size()) {
            ret.push_back(mem.top().first);
            mem.pop();
        }

        return ret;
    }
};

int main() {
  Solution s;
  vector<string> v = {
    //"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is",
    "i", "love", "leetcode", "i", "love", "coding"
  };

  int k = 2;
  for (auto s : s.topKFrequent(v, k)) {
    cout << s << ',';
  }
  cout << endl;
  return 0;
}
