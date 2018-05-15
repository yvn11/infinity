#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool is_greater(string a, string b) {
        int h_a = atoi(a.substr(0,2).c_str());
        int h_b = atoi(b.substr(0,2).c_str());
        
        if (h_a > h_b)
            return true;
        int m_a = atoi(a.substr(3,2).c_str());
        int m_b = atoi(b.substr(3,2).c_str());
        
        if (h_a == h_b && m_a > m_b)
            return true;
        
        return false;
    }
    
    int min_delta(string a, string b) {
        int h_a = atoi(a.substr(0,2).c_str());
        int h_b = atoi(b.substr(0,2).c_str());
        int m_a = atoi(a.substr(3,2).c_str());
        int m_b = atoi(b.substr(3,2).c_str());
        
        int ret = 24*60;
        ret = min(ret, is_greater(a, b) ? 
                  h_a*60+m_a-h_b*60-m_b : h_b*60+m_b-h_a*60-m_a);
        ret = min(ret, is_greater(a, b) ? 
                  (h_b+24)*60+m_b-h_a*60-m_a : (h_a+24)*60+m_a-h_b*60-m_b);
        return ret;
    }
    
    int findMinDifference(vector<string>& timePoints) {
        int ret = 24*60;
       
        sort(timePoints.begin(), timePoints.end());

        for (int i = 1; i < timePoints.size(); ++i) {
            ret = min(ret, min_delta(timePoints[i], timePoints[i-1]));
            if (i+1 < timePoints.size())
                ret = min(ret, min_delta(timePoints[i], timePoints[i+1]));
            if (i > 1)
                ret = min(ret, min_delta(timePoints[i], timePoints[0]));
        }
        return ret;
    }
};


int main() {
  Solution s;
  vector<string> v = {"05:31","22:08","00:35"};//{"23:59", "00:00"};
  cout << s.findMinDifference(v) << endl;
  return 0;
}
