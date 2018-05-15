#include <iostream>
#include <unordered_map>

using namespace std;

struct Block {
    int key;
    int val;
    Block *next;
    Block *prev;
    
    Block() {}

    Block(int key, int val) 
        : key(key), val(val), prev(nullptr), next(nullptr) {
        
    }
};


class LRUCache {
private:
    int cap;
    unordered_map<int, Block*> mem;
    Block *head;
public:
    LRUCache(int capacity):cap(capacity),head(nullptr) {
    }
    
    ~LRUCache() {
        delete(head);
        head = nullptr;
    }
    
    void set_head(Block *node) {
        if (!node)
          return;

        if (!head) {
          head = node;
          head->next = head->prev = head;
          return;
        }

        if (node->prev) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        node->next = head;
        node->prev = head->prev;
        node->prev->next = node;
        head->prev = node;
        head = node;
    }

    void remove_tail() {
        Block *p = head->prev;
        head->prev = head->prev->prev;
        head->prev->next = head;
        mem.erase(p->key);
        delete(p);
        p = nullptr;
    }

    int get(int key) {
        unordered_map<int, Block*>::iterator it = mem.find(key);

        if (it == mem.end()) {
          return -1;
        }

        set_head(it->second);
        return head->val;
    }
    
    void put(int key, int value) {
        unordered_map<int, Block*>::iterator it = mem.find(key);

        if (it != mem.end()) {
          it->second->val = value;
          set_head(it->second);
          return;
        }

        Block *p = new Block(key, value);

        if (mem.size() < cap) {
            set_head(p);
            mem.insert(make_pair(key, head));
        } else {
            set_head(p);
            mem.insert(make_pair(key, head));
            remove_tail();
        }
    }
};


int main() {
  LRUCache obj(10);
  obj.put(2, 1);
  obj.put(3, 2);
  cout << obj.get(3) << endl;
  cout << obj.get(2) << endl;
  obj.put(4, 3);
  cout << obj.get(2) << endl;
  cout << obj.get(3) << endl;
  cout << obj.get(4) << endl;
  obj.put(1, 1);
  obj.put(2, 2);
  cout << obj.get(1) << endl;
  obj.put(3, 3);
  cout << obj.get(2) << endl;
  obj.put(4, 4);
  cout << obj.get(4) << endl;
  obj.put(4, 1);
  cout << obj.get(4) << endl;
  cout << obj.get(3) << endl;
  cout << obj.get(2) << endl;
  cout << obj.get(1) << endl;
  obj.put(5, 5);
  cout << obj.get(1) << endl;
  cout << obj.get(2) << endl;
  cout << obj.get(3) << endl;
  cout << obj.get(4) << endl;
  cout << obj.get(5) << endl;
  obj.put(4, 3);
  cout << obj.get(2) << endl;
  cout << obj.get(3) << endl;
  cout << obj.get(4) << endl;
  obj.put(1, 1);
  obj.put(2, 2);
  cout << obj.get(1) << endl;
  return 0;
}
