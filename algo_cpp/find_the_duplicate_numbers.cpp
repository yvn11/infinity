#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        vector<int> mem(nums.size(), 0);
        
        for (int n : nums) {
            mem[n-1]++;
        }
        
        for (int n : nums) {
            if (mem[n-1] > 1)
                return n;
        }
        
        return 0;
    }
};

int main() {
  Solution s;
  vector<int> v = {3, 2, 7, 4, 6, 5, 1, 3};
  cout << s.findDuplicate(v) << endl;
  return 0;
}
