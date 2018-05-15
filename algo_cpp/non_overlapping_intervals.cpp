#include <iostream>
#include <vector>
#include <algorithm>
#include "interval.h"

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        if (intervals.empty())
            return 0;
        
        sort(intervals.begin(), intervals.end(), 
            [](const Interval& a, const Interval &b){
              if (a.start < b.start) return true;
              return a.end < b.end;
            });
        
        int end = intervals[0].end, ret = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].start < end) {
                ++ret;
            } else {
                end = intervals[i].end;
            }
        }
        
        return ret;
    }
};


int main() {
  Solution s;
  vector<Interval> v = {Interval(1,100), Interval(11,12), Interval(1,11), Interval(2,12)};
  cout << s.eraseOverlapIntervals(v) << endl;
  return 0;
}
