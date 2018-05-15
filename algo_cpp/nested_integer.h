#include <vector>
 
using namespace std;

class NestedInteger {
private:
  int _int_val;
  vector<NestedInteger> _list_val;
  bool _is_int;
public:

  NestedInteger() : _is_int(false) {}
  NestedInteger(int v) : _int_val(v), _is_int(true) {}
  NestedInteger(vector<NestedInteger> val) 
    : _list_val(val), _is_int(false) {}

  bool isInteger() const {
    return _is_int;
  }
  int getInteger() const {
    return _int_val;
  }
  const vector<NestedInteger> &getList() const {
    return _list_val;
  }
 };

