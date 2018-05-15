#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int j = 0, l = 0;

        if (nums.empty())
          return 0;
        
        while (j < nums.size()) {
            int c = 0;

            while (j < nums.size()-1) {
              if (nums[j] != nums[j+1]) {
                c = 0;
                nums[l++] = nums[j++];
              } else if (++c < 2) {
                nums[l++] = nums[j++];
              } else {
                break;
              }
            }
            
            if (j == nums.size()-1) {
                if (nums[j] != nums[l]);
                  nums[l++] = nums[j];
                break;
            }
            
            while (j < nums.size()-1 && nums[j] == nums[j+1])
                ++j;
        }

        return l;
    }
};


int main() {
  Solution s;
  vector<int> v = {1,1,1,2,4,4};
 
  int l = s.removeDuplicates(v);
  for (int i; i < l; ++i) {
    cout << v[i] << ',';
  }
  cout << endl;
  return 0;
}
