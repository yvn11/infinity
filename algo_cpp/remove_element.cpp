#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0, n = nums.size();
        
        while (i <= n) {
            if (nums[i] == val) {
                if (i == n-1) {
                    //nums.erase(nums.begin()+i);
                    n--;
                } else {
                    for (int p = i, j = i+1; j < nums.size(); ++j, ++p) {
                        nums[p] = nums[j];
                    }
                    n--;
                }
            } else {
              i++;
            }
        }
        return max(0, n);
    }
};

int main() {
  Solution s;
  vector<int> v = {3,3};
  cout << s.removeElement(v, 3) << endl;
  return 0;
}
