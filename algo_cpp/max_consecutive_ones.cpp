#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
      int ret = 0, j = 0;
      for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == 1) {
          ++j;
        } else {
          ret = max(ret, j);
          j = 0;
        }
      }
      ret = max(ret, j);
      return ret;
    }
};


int main() {
  Solution s;
  vector<int> v = {1,1,1,0,1,1,1,1,0,1,1};
  v = {0};
  cout << s.findMaxConsecutiveOnes(v) << endl;
  return 0;
}
