#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    int get_count(int num, unordered_map<int, int> &mem) {
        if (mem.find(num) != mem.end()) {
            return mem[num];
        }
        
        if (num == 0 || num == 1) {
            mem[num] = num;
            return mem[num];
        }
        
        int ret = 0;

        if (num % 2) {
          ret = get_count(num-1, mem)+1;
        } else {
          ret = get_count(num/2, mem);
        }

        return mem[num] = ret;
    }
    
    vector<int> countBits(int num) {
        unordered_map<int, int> mem;
        vector<int> ret;
        
        for (int i = 0; i <= num; ++i) {
          ret.push_back(get_count(i, mem));
        }
        return ret;
    }
};

int main() {
  Solution s;
  for (auto n : s.countBits(10)) {
    cout << n << ',';
  }
  cout << endl;
  return 0;
}
