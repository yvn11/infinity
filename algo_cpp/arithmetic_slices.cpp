#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        if (A.size() < 3)
            return 0;
        
        vector<vector<bool>> mem(A.size()+1, vector<bool>(A.size(), false));
        int ret = 0;
        
        for (int i = 0; i + 3 <= A.size(); ++i) {
            if (A[i+2]-A[i+1] == A[i+1]-A[i]) {
                mem[3][i] = true;
                ret++;
            }
        }
        
        for (int l = 4; l <= A.size(); ++l) {
            for (int i = 0; i + l <= A.size(); ++i) {
                mem[l][i] = mem[l-1][i] && mem[l-1][i+1];
                if (mem[l][i])
                    ret++;
            }
        }
        
        return ret;
    }
};

int main() {
  Solution s;
  vector<int> v = {1,3,5,7,9};
  cout << s.numberOfArithmeticSlices(v) << endl;
  return 0;
}
