#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return *(nums.begin()+(nums.size()-k));
    }
};


int main() {
  Solution s;
  vector<int> v = {21,3,5,1,6,11};
  cout << s.findKthLargest(v, 3) << endl;
  return 0;
}
