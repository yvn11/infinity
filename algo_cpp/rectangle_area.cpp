#include <iostream>

using namespace std;

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int all = (C-A)*(D-B)+(G-E)*(H-F);
        int ol_l = max(A, E), ol_r = max(ol_l, min(C, G));
        int ol_b = max(B, F), ol_t = max(ol_b, min(D, H));

//        ol_w = (E >= A && E <= C) ? C-max(A, E) : ((G >= A && G <= C) ? G-max(A, E) : 0);
//        ol_h = (H >= B && H <= D) ? D-max(B, H) : ((F >= B && F <= D) ? D-max(B, F) : 0);

        return all-((ol_r-ol_l)*(ol_t-ol_b));
    }
};


int main() {
  Solution s;
  cout << s.computeArea(-3, 0, 3, 4, 0, -1, 9, 2) << endl;
  cout << s.computeArea(0, -1, 9, 2, -3, 0, 3, 4) << endl;
  cout << s.computeArea(1, 1, 3, 9, 5, 5, 8, 9) << endl;
  cout << s.computeArea(-2, -2, 2, 2, -2, -2, 2, 2) << endl;
  return 0;
}
