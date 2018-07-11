#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Solution {
public:
    void do_search(vector<int> &nums, int target, 
                   int begin, int end,
                   int &r_begin, int &r_end) {
        if (end < begin) {
            return;
        }

        if (nums[begin] == target) {
            r_begin = min(r_begin, begin);
            r_end = max(r_end, begin);
        }

        if (nums[end] == target) {
            r_end = max(r_end, end);
            r_begin = min(r_begin, end);
        } 

        if (begin == end) {
          return;
        }

        int mid = (begin+end)/2;

        if (nums[mid] == target) {
            r_begin = min(r_begin, mid);
            r_end = max(r_end, mid);
            this->do_search(nums, target, mid+1, end, r_begin, r_end);
            this->do_search(nums, target, begin, mid-1, r_begin, r_end);
            return;
        }
        
        if (nums[mid] < target) {
            this->do_search(nums, target, mid+1, end, r_begin, r_end);
        } else {
            this->do_search(nums, target, begin, mid, r_begin, r_end);
        }
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        int begin = nums.size(), end = -1;
        this->do_search(nums, target, 0, nums.size()-1, begin, end);
        
        if (begin == nums.size()) {
          begin = -1;
        }
        return vector<int>{begin, end};
    }
};


int main() {
  Solution s;
  vector<int> v = {1,2,3,3,3,3,4,5,9};//5, 7, 7, 8, 8, 10};
  for (auto n : s.searchRange(v, 3)) {
    cout << n << ',';
  }
  cout << endl;
  return 0;
}
