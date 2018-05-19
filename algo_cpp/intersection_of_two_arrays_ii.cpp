#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
      sort(nums1.begin(), nums1.end());
      sort(nums2.begin(), nums2.end());
      
      int i = 0, j = 0;
      vector<int> ret;
      
      if (nums1.empty() || nums2.empty())
        return ret;
      
      while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] == nums2[j]) {
          ret.push_back(nums1[i]);
          ++i; ++j;
        } else if (nums1[i] < nums2[j]) {
          ++i;
        } else {
          ++j;
        }
      }
      
      return ret;
    }
};


int main() {
  Solution s;
  vector<int> v1 = {1,2,4,6,72,9,3};
  vector<int> v2 = {4,6,72,3};

  for (auto n : s.intersect(v1, v2))
    cout << n << ',';
  cout << endl;
  return 0;
}
