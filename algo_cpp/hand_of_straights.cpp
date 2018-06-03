#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>

using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
      if (hand.size() < W || hand.size() % W != 0)
        return false;

      sort(hand.begin(), hand.end());
      
      while (!hand.empty()) {
        int i = 0;
        vector<int> cur(1, INT_MIN);
        while (cur.size() < W+1 && i < hand.size()) {
          if (cur.size() == 1) {
            cur.push_back(hand[i]);
            hand.erase(hand.begin()+i);
            continue;
          }
          if (cur.back()+1 > hand[i]) {
            ++i; continue;
          }
          
          if (cur.back()+1 < hand[i]) {
            break;
          }
          cur.push_back(hand[i]);
          hand.erase(hand.begin()+i);
          
        }
        
        if (cur.size() < W+1)
          return false;
      }
      
      return true;
    }
};

int main() {
  Solution s;
  vector<int> v = {1,2,3,6,2,3,4,8,7};
  cout << s.isNStraightHand(v, 3) << endl;
  return 0;
}
