// Whether classes are the same
// Work with c++98 and c++03
#include <iostream>

using namespace std;

template<typename T, typename U>
struct is_same {
  static const bool value = false;
};

template<typename T>
struct is_same<T, T> {
  static const bool value = true;
};

template<class A, class B>
bool IsSameClass() {
  return is_same<A, B>::value;
};

class A {};
class B {};

int main() {
  cout << IsSameClass<A, B>() << endl;
  cout << IsSameClass<A, A>() << endl;
  return 0;
}
