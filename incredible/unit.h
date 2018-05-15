/* Incredible Unit
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include <vector>
#include <numeric>
#include <memory>
#include <algorithm>
#include "incredible/operation.h"

using namespace std;

namespace Incredible {


template<typename INPUT, typename OUTPUT>
class Unit {
  
  size_t _key;
  vector<shared_ptr<INPUT>> _inputs;
  vector<shared_ptr<OUTPUT>> _outputs;
  vector<Unit<INPUT, OUTPUT>> _depends;
  string _name;

public:
  /* A unit has multiple inputs from multiple units.
   */
  Unit() : _name("unit") {}
  /* Initialize a unit with numbers of inputs and outputs
   * this unit would use.
   * With `n_inputs` is 0, a unit has multiple inputs from multiple units.
   * A unit can be initialized as follow
   *
   * \code
   * Unit unit_prev(2, 1);
   * Unit unit_other(2, 1);
   * Unit unit_this(0, 1);
   * unit_this.add_input(unit_prev.outputs()[0]);
   * unit_this.add_input(unit_other.outputs()[0]);
   * \endcode
   */
  Unit(size_t n_inputs, size_t n_outputs) : _name("unit")
  {
    while (n_inputs--)
      _inputs.push_back(make_shared<INPUT>(0));
    while (n_outputs--)
      _outputs.push_back(make_shared<OUTPUT>(0));
  }
  /* Initialize with inputs and outputs from other units or 
   * pre-allocated storage.
   */
  Unit(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) 
  : _inputs(inputs), _outputs(outputs), _name("unit")
  {}
  /* Initialize with another unit's outputs as inputs
   * Unit unit_middle(<OP>, 2, 1);
   * // .. do some initialization ...
   * Unit unit_final(<OP>, middle.outputs, 1);
   */
  Unit(const vector<shared_ptr<OUTPUT>> &outputs, size_t n_outputs)
  : _inputs(outputs), _name("unit")
  {
    _outputs.resize(n_outputs);
  }

  virtual ~Unit() {}

  void add_input(const shared_ptr<OUTPUT>& input) {
    _inputs.push_back(input);
  }

  vector<shared_ptr<INPUT>>& inputs() {
    return _inputs;
  }

  vector<shared_ptr<OUTPUT>>& outputs() {
    return _outputs;
  }

  vector<Unit<INPUT, OUTPUT>>& dependencies() {
    return _depends;
  }

  void name(string name) {
    _name = name;
  }

  string& name() {
    return _name;
  }

  void add_dependency(Unit<INPUT, OUTPUT>& unit) {
    _depends.push_back(unit);
  }

  /* Start operation on inputs and store the result in outputs. An operation 
   * result is returned to indicate operation status.
   */
  virtual OpResult run(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) { return OpResult(0, "Done"); };
  /* TODO: dependencies */
  virtual OpResult run() {
    for (auto &unit : _depends) {
      unit.run();
    }
    return run(_inputs, _outputs);
  }
};

template<typename INPUT, typename OUTPUT>
ostream& operator<< (ostream &o, Unit<INPUT, OUTPUT> &unit) {
    o << unit.name() << ": ";

    o << "in[";
    for_each(unit.inputs().begin(), unit.inputs().end(), [&](auto i) {o << *i << ", ";});

    o << "] out[";
    for_each(unit.outputs().begin(), unit.outputs().end(), [&](auto i) {o << *i << ", ";});

    return o << "]";
  }
/* Perform addition on inputs */
template<typename INPUT, typename OUTPUT>
class Add : public Unit<INPUT, OUTPUT> {
  public:
    typedef Add<INPUT, OUTPUT> TYPE;
    typedef Unit<INPUT, OUTPUT> BASE;
    Add() : BASE() { BASE::name("Add"); }
    Add(size_t n_inputs, size_t n_outputs) : BASE(n_inputs, n_outputs) { BASE::name("Add"); }
    Add(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) : BASE(inputs, outputs) { BASE::name("Add"); };
    Add(vector<shared_ptr<OUTPUT>> &inputs, size_t n_outputs) : BASE(inputs, n_outputs) { BASE::name("Add"); };

    OpResult run() override {
      if (BASE::inputs().size() < 2)
        return OpResult(1, "No enough parameters");

      if (BASE::outputs().size() < 1)
        return OpResult(2, "No enough space to store outputs");

      *BASE::outputs()[0] = *BASE::inputs()[0] + (*BASE::inputs()[1]);
      return OpResult(0, "Output updated");
    }
};

/* Perform substraction on inputs */
template<typename INPUT, typename OUTPUT>
class Sub : public Unit<INPUT, OUTPUT> {
  public:
    typedef Sub<INPUT, OUTPUT> TYPE;
    typedef Unit<INPUT, OUTPUT> BASE;
    Sub() : BASE() { BASE::name("Sub"); }
    Sub(size_t n_inputs, size_t n_outputs) : BASE(n_inputs, n_outputs) { BASE::name("Sub"); }
    Sub(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) : BASE(inputs, outputs) { BASE::name("Sub"); };
    Sub(vector<shared_ptr<OUTPUT>> &outputs, size_t n_outputs) : BASE(outputs, n_outputs) { BASE::name("Sub"); };

    OpResult run() override {
      if (BASE::inputs().size() < 2)
        return OpResult(1, "No enough parameters");

      if (BASE::outputs().size() < 1)
        return OpResult(2, "No enough space to store outputs");

      *BASE::outputs()[0] = *BASE::inputs()[0] - (*BASE::inputs()[1]);
      return OpResult(0, "Output updated");
    }
};

/* Perform multiplication on inputs */
template<typename INPUT, typename OUTPUT>
class Mul : public Unit<INPUT, OUTPUT> {
  public:
    typedef Mul<INPUT, OUTPUT> TYPE;
    typedef Unit<INPUT, OUTPUT> BASE;
    Mul() : BASE() { BASE::name("Mul"); }
    Mul(size_t n_inputs, size_t n_outputs) : BASE(n_inputs, n_outputs) { BASE::name("Mul"); }
    Mul(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) : BASE(inputs, outputs) { BASE::name("Mul"); };
    Mul(vector<shared_ptr<OUTPUT>> &outputs, size_t n_outputs) : BASE(outputs, n_outputs) { BASE::name("Mul"); };

    OpResult run() override {
      if (BASE::inputs().size() < 2)
        return OpResult(1, "No enough parameters");

      if (BASE::outputs().size() < 1)
        return OpResult(2, "No enough space to store outputs");

      *BASE::outputs()[0] = *BASE::inputs()[0] * (*BASE::inputs()[1]);
      return OpResult(0, "Output updated");
    }
};

/* Perform division on inputs */
template<typename INPUT, typename OUTPUT>
class Div : public Unit<INPUT, OUTPUT> {
  public:

    typedef Div<INPUT, OUTPUT> TYPE;
    typedef Unit<INPUT, OUTPUT> BASE;
    Div() : BASE() { BASE::name("Div"); }
    Div(size_t n_inputs, size_t n_outputs) : BASE(n_inputs, n_outputs) { BASE::name("Div"); }
    Div(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) : BASE(inputs, outputs) { BASE::name("Div"); };
    Div(vector<shared_ptr<OUTPUT>> &outputs, size_t n_outputs) : BASE(outputs, n_outputs) { BASE::name("Div"); };

    OpResult run() override {
      if (BASE::inputs().size() < 2)
        return OpResult(1, "No enough parameters");

      if (BASE::outputs().size() < 1)
        return OpResult(2, "No enough space to store outputs");

      if (*BASE::inputs()[1] == 0)
        return OpResult(3, "Divided by zero");

      *BASE::outputs()[0] = *BASE::inputs()[0] / (*BASE::inputs()[1]);
      return OpResult(0, "Output updated");
    }
};

/* Perform modulus on inputs */
template<typename INPUT, typename OUTPUT>
class Mod : public Unit<INPUT, OUTPUT> {
  public:
    typedef Mod<INPUT, OUTPUT> TYPE;
    typedef Unit<INPUT, OUTPUT> BASE;
    Mod() : BASE() { BASE::name("Mod"); }
    Mod(size_t n_inputs, size_t n_outputs) : BASE(n_inputs, n_outputs) { BASE::name("Mod"); }
    Mod(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) : BASE(inputs, outputs) { BASE::name("Mod"); };
    Mod(vector<shared_ptr<OUTPUT>> &outputs, size_t n_outputs) : BASE(outputs, n_outputs) { BASE::name("Mod"); };

    OpResult run() override {
      if (BASE::inputs().size() < 2)
        return OpResult(1, "No enough parameters");

      if (BASE::outputs().size() < 1)
        return OpResult(2, "No enough space to store outputs");

      if (*BASE::inputs()[1] == 0)
        return OpResult(3, "Divided by zero");

      *BASE::outputs()[0] = *BASE::inputs()[0] % *BASE::inputs()[1];
      return OpResult(0, "Output updated");
    }
};

/* Perform negation on input */
template<typename INPUT, typename OUTPUT>
class Negate : public Unit<INPUT, OUTPUT> {
  public:
    typedef Negate<INPUT, OUTPUT> TYPE;
    typedef Unit<INPUT, OUTPUT> BASE;
    Negate() : BASE() { BASE::name("Negate"); }
    Negate(size_t n_inputs, size_t n_outputs) : BASE(n_inputs, n_outputs) { BASE::name("Negate"); }
    Negate(vector<shared_ptr<INPUT>> &inputs, vector<shared_ptr<OUTPUT>> &outputs) : BASE(inputs, outputs) { BASE::name("Negate"); };
    Negate(vector<shared_ptr<OUTPUT>> &outputs, size_t n_outputs) : BASE(outputs, n_outputs) { BASE::name("Negate"); };

    OpResult run() override {
      if (BASE::inputs().size() < 1)
        return OpResult(1, "No enough parameters");

      if (BASE::outputs().size() < 1)
        return OpResult(2, "No enough space to store outputs");

      *BASE::outputs()[0] = -(*BASE::inputs()[0]);
      return OpResult(0, "Output updated");
    }
};

} // namespace Incredible 
