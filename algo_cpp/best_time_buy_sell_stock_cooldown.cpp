#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty())
            return 0;
        
        int ret = 0;
        
        vector<int> buy(prices.size(), 0),
            sell(prices.size(), 0),
            cool(prices.size(), 0);

        sell[0] = 0;
        buy[0] = -prices[0];
        cool[0] = 0;

        for (int i = 1; i < prices.size(); ++i) {
          sell[i] = max(buy[i-1]+prices[i], sell[i-1]);
          buy[i] = max(cool[i-1]-prices[i], buy[i-1]);
          cool[i] = max(cool[i-1], max(buy[i-1], sell[i-1]));
        }

        ret = max(cool[prices.size()-1], sell[prices.size()-1]);

        return ret;
    }
};


int main() {
  Solution s;
  vector<int> v = {1,2,4};//,3,0,2};
  cout << s.maxProfit(v);
  return 0;
}
