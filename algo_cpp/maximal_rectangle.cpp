#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int do_max_rect(vector<vector<char>>& matrix, vector<vector<char>> &mem,
                   int m, int n) {
        if (m < 0 || n < 0 || m >= matrix.size() || n >= matrix[0].size()) {
          return 0;
        }

        if (mem[m][n] != '-') {
            return 0;
        }

        if (matrix[m][n] == '0') {
            mem[m][n] = '0';
            return 0;
        }

        int m_cur = 1;
        mem[m][n] = '1';

        m_cur += this->do_max_rect(matrix, mem, m+1, n);
//        m_cur += this->do_max_rect(matrix, mem, m-1, n);
        m_cur += this->do_max_rect(matrix, mem, m, n+1);
//        m_cur += this->do_max_rect(matrix, mem, m, n-1);

        return m_cur;
    }

    int strip_rect(vector<vector<char>>& mem, int m_rect) {
        bool del = false;
    
        for (int i = 0; i < mem.size(); ++i) {
            del = false;

            for (int j = 0; j < mem[0].size(); ++j) {
                if (mem[i][j] == '0') {
                    del = true;
                    break;
                }
            }

            if (del) {
                for (int j = 0; j < mem[0].size(); ++j) {
                    if (mem[i][j] == '1') {
                        m_rect--;
                    }
                }
            }
        }
        return m_rect;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();

        if (m == 0) 
          return 0;

        int n = matrix[0].size();
        int ret = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                vector<vector<char>> mem(m, vector<char>(n, '-'));
                int rect = this->do_max_rect(matrix, mem, i, j);
                if (rect == 0)
                  continue;
                rect = this->strip_rect(mem, rect);
                ret = max(ret, rect);
            }
        }
        return ret;
    }
};


int main() {
  Solution s;
  vector<vector<char>> v = {{'1', '0'}};
  /*
    {'1', '0', '1', '0', '0'},
    {'1', '0', '1', '1', '1'},
    {'1', '1', '1', '1', '1'},
    {'1', '0', '0', '1', '0'},
  };
  */
  cout << s.maximalRectangle(v) << endl;
  return 0;
}
