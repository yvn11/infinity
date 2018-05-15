#include <iostream>
#include <unordered_set>
#include <random>

using namespace std;

class RandomizedSet {
private:
    unordered_set<int> mem;

public:
    RandomizedSet() {
    }
    
    bool insert(int val) {
      if (mem.find(val) == mem.end()) {
        mem.insert(val);
        return true;
      }
      return false;
    }
    
    bool remove(int val) {
       unordered_set<int>::iterator it = this->mem.find(val);
       if (it != mem.end()) {
         mem.erase(it);
         return true;
       }
       return false;
    }
    
    int getRandom() {
       uniform_int_distribution<int> dist(0, mem.size()-1);
       random_device dev;
       mt19937 eng(dev());

       unordered_set<int>::iterator it = mem.begin();
       advance(it, dist(eng));
       return *it;
    }
};

int main() {
  RandomizedSet obj = RandomizedSet();
  cout << obj.insert(17) << endl;
  cout << obj.insert(14) << endl;
  cout << obj.insert(99) << endl;
  cout << obj.insert(3) << endl;
  int k = 10;while (k--) cout << obj.getRandom() << endl;
  cout << obj.remove(3) << endl;
  cout << obj.remove(3) << endl;
  return 0;
}
