#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    int hamming_dist(int a, int b) {
      int len = 0;
      int c = a ^ b;
      int k = 32;

      if (a == b)
        return len;

      while (k--) {
        c >>= 1;
        if (c & 1) len++;
      }
      return len;
    }

    int calc_hamming(vector<int>& nums) {
       int ret = 0;

       for (int i = 0; i < nums.size(); ++i) {
          for (int j = i+1; j < nums.size(); ++j) {
            ret += hamming_dist(nums[i], nums[j]);
          }
       }
       return ret;
    }

    int calc_bit(vector<int>& nums) {
        int ret = 0;
        
        for (int i = 0; i < 32; ++i) {
          int c = 0;
          for (auto n : nums) {
            if (n & (1 << i))
              c++;
          }
          ret += c * (nums.size()-c);
        }
        return ret;
    }

    int totalHammingDistance(vector<int>& nums) {
       //return calc_hamming(nums);
       return calc_bit(nums);
    }
};


int main() {
  Solution s;
  vector<int> v = {
 //   4, 14, 2};
  6,1,8,6,8};
  cout << s.totalHammingDistance(v) << endl;
  return 0;
}
