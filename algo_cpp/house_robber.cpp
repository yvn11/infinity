#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
      if (nums.empty())
        return 0;

      int even = 0, odd = 0;

      for (int i = 0; i < nums.size(); ++i) {
        if (i % 2) {
          even = max(odd, even+nums[i]);
        } else {
          odd = max(even, odd+nums[i]);
        }
      }

      return max(even, odd);
    }
};


int main() {
  Solution s;
  vector<int> v = {3, 5, 1, 6, 8};
  cout << s.rob(v) << endl;
  return 0;
}
