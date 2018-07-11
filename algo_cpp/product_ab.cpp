#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* B[i] is product of A without A[i] */
void product(vector<int> &A, vector<int> &B) {
  int prod = 1;

  for (int i = 0; i < A.size(); ++i) {
    B[i] = prod;
    prod *= A[i];
  }

  prod = 1;
  for (int i = A.size()-1; i >= 0; --i) {
    B[i] *= prod;
    prod *= A[i];
  }
}


int main() {
  vector<int> a = {1,2,4,0,3};
  vector<int> b(a.size());
  product(a, b);
  for_each(b.begin(), b.end(), [&](auto c) {cout << c << ',';});
  return 0;
}
