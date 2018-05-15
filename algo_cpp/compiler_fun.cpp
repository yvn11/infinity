#include <iostream>

using namespace std;

int main() {
  int v = 518;
  cout << "0x" << hex << v << dec << endl;
  cout << "total 1s:" << __builtin_popcount(v) << endl;
  cout << "total 1s is even:" << __builtin_parity(v) << endl;
  cout << "total 0s at begining:" << __builtin_ctz(v) << endl;
  cout << "total 0s at end:" << __builtin_clz(v) << endl;
  
  if (__builtin_expect(3, 3))
    cout << "expect 3 == 3" << endl;
  if (__builtin_expect(3 == 4, 1))
    cout << "expect 3 != 4" << endl;

  if (__builtin_constant_p(v))
    cout << v << " is constant" << endl;

  const int color = 100;
  if (__builtin_constant_p(color))
    cout << color << " is constant" << endl;

  int hole(1999); 
  __builtin_prefetch(&hole, 1, 1);
  cout << "number in hole:" << hole << endl;

  cout << "huge value(double):" << __builtin_huge_val() << endl;
  cout << "huge value(float):" << __builtin_huge_valf() << endl;
  cout << "huge value(long):" << __builtin_huge_vall() << endl;
  cout << "infinite value(int32):" << (int)__builtin_infd32() << endl;
  cout << "infinite value(int64):" << (int)__builtin_infd64() << endl;
  cout << "infinite value(int128):" << (int)__builtin_infd128() << endl;
  cout << "nan:" << __builtin_nan("") << endl;
  
  int byter = 0xabcdef;
  cout << "reverse(16) " << hex << byter << ": " << __builtin_bswap16(byter) << dec << endl;
  cout << "reverse(32) " << hex << byter << ": " << __builtin_bswap32(byter) << dec << endl;
  cout << "reverse(64) " << hex << byter << ": " << __builtin_bswap64(byter) << dec << endl;

  cout << "power: " << __builtin_pow(2, 3) << endl;
  cout << "power(float): " << __builtin_powf(3.5, 2) << endl;


  cout << __builtin_FILE() << ":" << __builtin_FUNCTION() << ":"
    << __builtin_LINE() << endl;

  __builtin_trap();
  cout << "won't reach" << endl;
  return 0;
}
