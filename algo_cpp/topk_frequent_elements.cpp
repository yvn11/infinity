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
    vector<int> heap_way(vector<int>& nums, int k) {
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

    vector<int> hash_way(vector<int>& nums, int k) {
      unordered_map<int, vector<int>> mem;
      vector<int> cache;
      vector<int> ret;

      sort(nums.begin(), nums.end());
      int i = 0, freq = 1;

      while (i < nums.size()) {
        while (i < nums.size()-1 && nums[i] == nums[i+1]) {
          ++freq; ++i;
        }

        if (mem.find(freq) == mem.end()) {
          cache.push_back(freq);
        }

        mem[freq].push_back(nums[i]);
        freq = 1;
        ++i;
      }

      sort(cache.begin(), cache.end());

      for (int i = cache.size()-1; i >= 0 && ret.size() < k; --i) {
        int j = 0;
        while (ret.size() < k && j < mem[cache[i]].size()) {
          ret.push_back(mem[cache[i]][j++]);
        }
      }
  
      return ret;
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
      return heap_way(nums, k);
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
