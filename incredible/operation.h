/* Incredible Operation
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

namespace Incredible {

struct OpResult {
  int code;
  std::string msg;

  OpResult(int code, std::string msg) 
  : code(code), msg(msg)
  {}
};

/*
template<typename INPUT, typename OUTPUT>
class Operation {
    std::string _name;
  public:
    //typedef typename INPUT Operation::INPUT INPUT;
    //typedef typename Operation::OUTPUT OUTPUT;
    Operation<INPUT, OUTPUT>(std::string name) : _name(name) {};
    Operation<INPUT, OUTPUT>() : _name("op") {};
    void name(std::string name) { _name = name; }
    string& name() { return _name; }
    virtual OpResult run() { return OpResult(0, "Done"); }
    virtual OpResult run(vector<INPUT> &inputs, vector<OUTPUT> &outputs) { return OpResult(0, "Done"); };
};
*/
} // namespace Incredible 
