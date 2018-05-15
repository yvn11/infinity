#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class Solution {
public:
    
    int shape(int px1, int py1, int px2, int py2) {
        return abs(px2-px1)*min(py1, py2);
    }
    
    int maxArea(vector<int>& height) {
        int ret = -1;
        int i = 0, j = height.size()-1;
        
        while (j >= i) {
            ret = max(ret, shape(i, height[i], j, height[j]));
        
            if (height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }
        return ret;
    }
};

int main() {
  Solution s;
  vector<int> height = {3,2,6,5,1};
  cout << s.maxArea(height) << '\n';
  return 0;
}
