#include <iostream>
#include <unordered_map>

using namespace std;

struct Cache {
  int key;
  int value;
  int freq;
  Cache *prev, *next;
  Cache() {}
  Cache(int key, int value) : key(key), value(value), freq(1)
  {
    prev = this; next = this;
  }
};

class LFUCache {
private:
  unordered_map<int, Cache*> _mem;
  unordered_map<int, Cache*> _freq;
  int _capacity, _mi_freq;

public:
    LFUCache(int capacity) : _capacity(capacity), _mi_freq(1) {
    
    }
    
    Cache* add_front(Cache* head, Cache* node) {
      if (!head) {
        node->next = node->prev = node;
        return node;
      }

      node->next = head;
      node->prev = head->prev;
      head->prev->next = node;
      head->prev = node;

      return node;
    }

    Cache* remove_node(Cache* head, Cache* node) {
      if (!node)
        return head;
      
      if (node == node->next) {
        head = nullptr;
        return nullptr;
      }

      node->prev->next = node->next;
      node->next->prev = node->prev;
      if (head == node) {
        return node->next;
      }
      return head;
    }

    int get(int key) {
      if (_mem.find(key) == _mem.end()) {
        return -1;
      }

      Cache* p = _mem[key];
      int ret = p->value;

      Cache* old = _freq[p->freq];
      _freq[p->freq] = remove_node(old, p); 

      if (_mi_freq == p->freq && !_freq[p->freq])
        ++_mi_freq;

      ++(p->freq);
      Cache* head = _freq.find(p->freq) != _freq.end() ? _freq[p->freq] : nullptr;
      _freq[p->freq] = add_front(head, p);

      return ret;
    }
    
    void put(int key, int value) {
        if (_capacity == 0)
          return;

        if (_mem.find(key) != _mem.end()) {
          _mem[key]->value = value;
          get(key);
          return;
        }
 
        Cache* p = new Cache(key, value); 
 
        if (_mem.size() == _capacity) {
          Cache* old =_freq[_mi_freq], *q = old->prev;
          _mem.erase(q->key);
          _freq[_mi_freq] = remove_node(old, q);
          delete q;
          q = nullptr;
        }
 
        _mem[key] = p;
        Cache* head = _freq.find(p->freq) != _freq.end() ?_freq[p->freq] : nullptr;
        _freq[p->freq] = add_front(head, p);
        _mi_freq = p->freq;
    }
};


int main() {
  LFUCache obj(2);


  obj.put(1, 1);
  obj.put(2, 2);
  cout << obj.get(1) << endl;
  obj.put(3, 3);
  cout << obj.get(2) << endl;
  cout << obj.get(3) << endl;
  obj.put(4, 4);
  cout << obj.get(1) << endl;
  cout << obj.get(3) << endl;
  cout << obj.get(4) << endl;
/*
  obj.put(3, 3);
  obj.put(9, 9);
  cout << obj.get(3) << ',' << 3 << endl;
  obj.put(4, 4);
  cout << obj.get(9) << ',' << -1 << endl;
  cout << obj.get(4) << ',' << 4 << endl;
  cout << obj.get(3) << ',' << 3 << endl;
  cout << obj.get(3) << ',' << 3 << endl;
  obj.put(5, 5);
  cout << obj.get(5) << ',' << 5 << endl;
  cout << obj.get(4) << ',' << -1 << endl;
  cout << obj.get(3) << ',' << 3 << endl;
*/
  return 0;
}
