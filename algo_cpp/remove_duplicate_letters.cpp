#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        if (!s.length()) 
          return s;

        string ret;
        vector<int> mem(26, 0);

        for (auto c : s) {
          mem[c-'a']++;
        }

        for (auto c : s) {
          mem[c-'a']--;

          if (ret.find(c) != string::npos) {
            continue;
          }

          while (ret.length() && c < ret.back() && mem[ret.back()-'a'] > 0)
              ret.pop_back();

          ret += c;
        }

        return ret;
    }
};

int main() {
  Solution s;
  string str("yiklorymxepctlnomfmymitulgfuudxturmemjxxlloevwyfriazwyckgbfogfrppnsomjfhoobirytzzksemgrcbcegbbhaurrrlyxquuoivdcykcpnntgrktwtmgstjrvsvajfukhxwgvsvgzwoatnnzszksxstzkojmyuriyriyqkaqghoxilykyxepnsjeybgxxwyyornzxzttsylsoqlumzwlsdxvzgjfpwwoejsieeyoremvqfyekmxdsabogijmqxdruiydlkrvobwqmlmahmfpwbopbdxhinowqavdasnkeagpjvznzfmlllydgosztljnkrkpjhsqtjxjumzasfitacjqenwcskkkifgzatcevfwererjjabmmmdsnuacxzrgjyytbmxccagjbemkmemjpaqwpjdsunvmfuromfhmumhlzycbhptfjuodlgjxuxcggtotaxjlqbccghyplvtgrwwlhmriwnecdhjmbpzdaqgpyhinawvmxjyiptiroxtuwybcjjkqcirscdqbakpwdiabgirknpvlwmvspufpdqchvbqbspyznfuscidqcbtcvwsqgjjdfpnuhgpxkgikvagtbhnssycxpefsqxbcgtubdmtcojbzpcjvfoslunoiixxdakfczg");
  cout << s.removeDuplicateLetters(str) << endl;
  return 0;
}
