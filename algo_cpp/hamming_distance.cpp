#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
  int hammingDistance(int x, int y) {
    int z = x^y;
    int ret = 0;
    while (z) {
      if (1 & z)
        ++ret;
      z >>= 1;
    }
    return ret;
  }

  int batch_hamming_dist(vector<int> nums) {
    int ret = 0;
    for (int i = 0; i < 32; ++i) {
      int c = 0;
      for (auto n : nums) {
        if (n & (1 << i)) ++c;
      }
      ret += c * (nums.size()-c);
    }
  }
};


int main() {
  Solution s;
  cout << s.hammingDistance(8, 7) << endl;
  cout << s.batch_hamming_dist(vector<int>{8, 7}) << endl;
  return 0;
}
