#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        
        vector<vector<int>> mem(nums.size(), vector<int>(nums.size(), 0));
        
        for (int i = 1; i < nums.size()-1; ++i) {
            for (int j = i; j > 0; --j) {
                for (int k = j; k <= i; ++k) {
                    mem[j][i] = max(mem[j][i], mem[j][k-1]+mem[k+1][i]+
                                   nums[k]*nums[j-1]*nums[i+1]);
                }
            }
        }
        
        return mem[1][nums.size()-2];
    }
};


int main() {
  Solution s;
  vector<int> v = {3,1,5,8};
  cout << s.maxCoins(v) << endl;
  return 0;
}
