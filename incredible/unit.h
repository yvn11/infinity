/* Incredible Unit
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include <vector>
#include <numeric>
#include <memory>
#include <algorithm>
#include "operation.h"


namespace Incredible {

using namespace std;

template<typename INPUT, typename OUTPUT>
class Unit {
  
  size_t _key;
  vector<shared_ptr<INPUT>> _inputs;
  vector<shared_ptr<OUTPUT>> _outputs;
  vector<shared_ptr<Unit<INPUT, OUTPUT>>> _depends;
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
    _inputs.reserve(n_inputs);
    for (size_t i = 0; i < n_inputs; ++i)
      _inputs.push_back(make_shared<INPUT>(0));

    _outputs.reserve(n_outputs);
    for (size_t i = 0; i < n_outputs; ++i)
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
    _outputs.reserve(n_outputs);
    for (size_t i = 0; i < n_outputs; ++i)
      _outputs.push_back(make_shared<OUTPUT>(0));
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

  void add_dependency(shared_ptr<Unit<INPUT, OUTPUT>> unit) {
    _depends.push_back(unit);
  }

  /* Start operation on inputs and store the result in outputs. An operation 
   * result is returned to indicate operation status.
   */
  virtual OpResult run() { return OpResult(0, "Done"); }
  /* Run after all dependencies are done
   */
  virtual OpResult run_all() {
    if (std::any_of(_depends.begin(), _depends.end(), 
          [&](auto &unit) { return (*unit).run().code != 0; }))
      return DependencyFail();
    return run();
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

} // namespace Incredible 
