/* Incredible Operation
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include <iostream>
#include <vector>
#include <numeric>

namespace Incredible {

using namespace std;


struct OpResult {
  int code;
  std::string msg;

  OpResult(int code, std::string msg) 
  : code(code), msg(msg)
  {}
};

ostream& operator<< (ostream &o, OpResult &res) {
  return o << res.code << ": " << res.msg;
}

struct OutputUpdated : OpResult {
  OutputUpdated() : OpResult(0, "Output updated") {}
};

struct DependencyFail : OpResult {
  DependencyFail() : OpResult(4, "Dependency failed") {}
};

struct NoEnoughSpace : OpResult {
   NoEnoughSpace() : OpResult(2, "No enough space to store outputs") {}
};

struct NoEnoughInputs : OpResult {
  NoEnoughInputs() : OpResult(3, "No enough parameters") {}
};

struct DivByZero : OpResult {
  DivByZero() : OpResult(4, "Divided by zero") {}
};



#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
template<typename INPUT, typename OUTPUT>
class [[deprecated]] Operation {
    std::string _name;
  public:
    Operation<INPUT, OUTPUT>(std::string name) : _name(name) {};
    Operation<INPUT, OUTPUT>() : _name("op") {};
    void name(std::string name) { _name = name; }
    string& name() { return _name; }
    virtual OpResult run() { return OpResult(0, "Done"); }
    virtual OpResult run(vector<INPUT> &inputs, vector<OUTPUT> &outputs) { return OpResult(0, "Done"); };
};


} // namespace Incredible 
