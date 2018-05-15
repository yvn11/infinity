#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> mem;
        vector<int> ret;
        
        for (auto n : nums1) {
            mem.insert(n);
        }
        
        for (auto n : nums2) {
            if (mem.find(n) != mem.end()) {
                ret.push_back(n);
                mem.erase(n);
            }
        }
        
        return ret;
    }
};

int main() {
  Solution s;
  vector<int> v1 = {3,2,4,2,1,6,7,1,1,9};
  vector<int> v2 = {5,2,1,7,9};

  for (auto n : s.intersection(v1, v2)) {
    cout << n << ',';
  }
  cout << endl;
  return 0;
}
