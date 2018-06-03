#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& A) {
      int ret = 0;
      
      for (int i = 1; i < A.size(); ++i) {
        if (A[i-1] >= A[i]) {
          continue;
        }
        int left = 0, right = 0, j = i;
        while (i < A.size()-1 && A[i] > A[i+1]) {
          ++i; ++right;
        }
        
        while (j > 0 && A[j] > A[j-1]) {
          --j; ++left;
        }

        if (left < 1 || right < 1)
          continue;
        
        int cur = 1 + left + right;
        if (cur < 3)
          continue;
        ret = max(ret, cur);
      }
      return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {2,1,3,5,7,4,3};  
  cout << s.longestMountain(v) << endl;
  return 0;
}
