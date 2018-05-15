#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int get_single(vector<int>& nums, int begin, int end) {
        if (end-begin == 0) {
            return nums[begin];
        }
        
        int mid = (begin+end)/2;
        
        if ((mid+1)%2) {
            if (nums[mid] == nums[mid+1])
                return get_single(nums, mid+1, end);
            else
                return get_single(nums, begin, mid);
        }
            
        if (nums[mid] == nums[mid-1])
            return get_single(nums, mid+1, end);
        return get_single(nums, begin, mid);
    }
    
    int singleNonDuplicate(vector<int>& nums) {
        if (nums.empty())
            return -1;
        return get_single(nums, 0, nums.size()-1);
    }
};

int main() {
  Solution s;
  vector<int> v = {1,1,2,2,3,3,4,4,9};
  cout << s.singleNonDuplicate(v) << endl;
  return 0;
}
