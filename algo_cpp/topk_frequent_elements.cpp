#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include <queue>

using namespace std;

struct compare{
  bool operator()(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
  }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ret;
        if (!nums.size() || !k)
          return ret;

        unordered_map<int, int> mem;

        for (auto n : nums)
          mem[n]++;

        priority_queue<pair<int, int>, vector<pair<int, int> >,
          compare> q(mem.begin(), mem.end());

        while (k-- > 0) {
          ret.push_back(q.top().first);
          q.pop();
        }

        return ret;
    }
};


int main() {
  Solution s;
  vector<int> v = {1,1,1,2,2,3};
  for (auto n : s.topKFrequent(v, 2))
    cout << n << ',';
  cout << endl;
  return 0;
}
