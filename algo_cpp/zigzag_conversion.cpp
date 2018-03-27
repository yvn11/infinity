#include <iostream>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        string ret;
        
        if (s.length() <= numRows || numRows == 1) {
            return s;
        }
        
        for (int r = 0; r < numRows; ++r) {
            if (r % 2 == 0) { 
                for (int i = r; i*numRows < s.length(); ++i) {
                    if (numRows % 2 != 0) {
                        ret += s[i*numRows+1];
                    } else {
                        ret += s[i*numRows];
                    }
                }
            } else {
                for (int i = r; i < s.length(); i=i+2) {
                    ret += s[i];
                }
            }
        }
        return ret;
    }
};

int main() {
  Solution s;
  cout << s.convert("ABC", 2) << '\n';
  cout << s.convert("jclvlazamucimicnewdoxjlfuemdadgkhufsuevjaxrnivcorhfrqqwnujquoyevslqprlyskrhunljgsoxleuyyfqutozqhmgyetyyepfaesjlkzivdevdllygazxjndjrxhrdyyddqnqdoayshwxshxzjywumbffamxdnxjqoyirmirernekxdlicjfqkkvnxuqmszcixmzkwsqoiwyfalpeuuugfrteomqinuqnirxelpstosaodqszkogrfbxtnpdbltqtmpyyeqtujuiokcowswqyxntndxqqsgkhvihbaawjugagloddktdjizynyoesuozryityjrifximkyrokktvusuiqiojfckyatryekijksvusokcyeavwufpctajxkixdbxjmitwcqqxfbbfhbadvfuaaujxfrwkvuuhepdifvfkyhsfiuleafgaapahjwtesplweqfmnmymtqreleinkopmfpvomqueghdmxkynwxzqnswaxgnjwdxbuusgkmnqwqdvadiwahoqakqzqgkmlhqfdimnwzgsplorownpgehioxhhfrvqalwdtksslykajataxgpdmyldxukdnftprrumbmemlrowrhwoqntclghlcrorzhgsbaecplpccdyvnxmdmfhaoplqizkhiqbjtimitdkxiksxjecwmkwabhslievqvwcqeqaztkydwrbgxdcjpalshgepkzhhv", 352) << '\n';
  cout << s.convert("ABCD", 2) << '\n';
  return 0;
}
