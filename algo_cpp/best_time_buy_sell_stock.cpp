#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty())
            return 0;
        int i = prices.size()-2, m = prices.size()-1;
        int ret = 0;
        
        for (; i < m && i >= 0; --i) {
            if (prices[m] > prices[i]) {
                ret = max(ret, prices[m]-prices[i]);
            } else {
                m = i;
            }
        }
        
        return ret;
    }
};


int main() {
  Solution s;
  vector<int> v = {7,1,5,3,6,4};
  cout << s.maxProfit(v) << endl;
  return 0;
}
