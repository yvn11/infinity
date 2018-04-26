#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Solution {
private:
    vector<int> mem;
public:
    Solution(vector<int> nums) {
      mem = nums;
    }
    
    int pick(int target) {
        int n = 0, ret = 0;

        for (int i = 0; i < mem.size(); ++i) {
            if (mem[i] != target)
                continue;
            if (n == 0)
                ret = i;
            if (rand() % ++n == 0)
                ret = i;
        }

        return ret;
    }
};

int main() {
  Solution s(vector<int>{1,2,2,3,3,3});
  cout << s.pick(3) << endl;
  cout << s.pick(3) << endl;
  cout << s.pick(3) << endl;
  cout << s.pick(3) << endl;
  return 0;
}
