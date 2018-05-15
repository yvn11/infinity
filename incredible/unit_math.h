/* Incredible Math Unit
 * Define general mathematics units
 *
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#pragma once
#include "unit.h"

namespace Incredible {

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
        return NoEnoughInputs();

      if (BASE::outputs().size() < 1)
        return NoEnoughSpace();

      *BASE::outputs()[0] = *BASE::inputs()[0] + (*BASE::inputs()[1]);
      return OutputUpdated();
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
        return NoEnoughInputs();

      if (BASE::outputs().size() < 1)
        return NoEnoughSpace();

      *BASE::outputs()[0] = *BASE::inputs()[0] - (*BASE::inputs()[1]);
      return OutputUpdated();
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
        return NoEnoughInputs();

      if (BASE::outputs().size() < 1)
        return NoEnoughSpace();

      *BASE::outputs()[0] = *BASE::inputs()[0] * (*BASE::inputs()[1]);
      return OutputUpdated();
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
        return NoEnoughInputs();

      if (BASE::outputs().size() < 1)
        return NoEnoughSpace();

      if (*BASE::inputs()[1] == 0)
        return DivByZero();

      *BASE::outputs()[0] = *BASE::inputs()[0] / (*BASE::inputs()[1]);
      return OutputUpdated();
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
        return NoEnoughInputs();

      if (BASE::outputs().size() < 1)
        return NoEnoughSpace();

      if (*BASE::inputs()[1] == 0)
        return DivByZero();

      *BASE::outputs()[0] = *BASE::inputs()[0] % *BASE::inputs()[1];
      return OutputUpdated();
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
        return NoEnoughInputs();

      if (BASE::outputs().size() < 1)
        return NoEnoughSpace();

      *BASE::outputs()[0] = -(*BASE::inputs()[0]);
      return OutputUpdated();
    }
};

} // namespace Incredible 
