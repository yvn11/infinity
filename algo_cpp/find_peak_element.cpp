#include <iostream>
#include <vector>

using namespace std;

class Solution {

public:
   int findPeakElement(vector<int> &nums) {
      if (nums.empty())
        return -1;

      int ret = 0;

      for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < nums[ret]) {
          continue;
        }
        ret = i;
      }

      return ret;
   }
};


int main() {
  Solution s;
  vector<int> v = {3,4,1,9,2,7,0};
  cout << s.findPeakElement(v) << endl;
  return 0;
}
