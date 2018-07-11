#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int power_count(int X, int N, int i, int total) {
    if (total == X)
        return 1;
    if (total > X)
        return 0;
    
    int ret = 0;
    int cur = pow(i, N);
    
    while (total+cur < X) {
        ret += power_count(X, N, i+1, total+cur);
        i++;
        cur = pow(i, N);
    }
    
    if (X == total+cur)
        ret += 1;
    
    return ret;
    
}

int main() {
    int X, N;
    cin >> X >> N;
    cout << power_count(X, N, 1, 0) << '\n';
    return 0;
}
