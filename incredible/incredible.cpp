/* Incredible Unit
 * Author: Zex Li <top_zlynch@yahoo.com>
 */
#include <iostream>
#include <vector>
#include "unit.h"

using namespace Incredible;

const std::string STOP_SIGN("POTS");

typedef Add<double, double> UNIT_DD_ADD;
typedef Negate<double, double> UNIT_DD_NEG;
typedef Mul<double, double> UNIT_DD_MUL;

class App {

public:
  App() {
  }

  /* Start a graph to complete the following computation 
   *
   *  add(input1, input2) * negate(input3) = outputs
   *
   */
  void start() {
    UNIT_DD_ADD unit1(2, 1);
    UNIT_DD_NEG unit3(1, 1);
    UNIT_DD_MUL unit2(0, 1);
    unit2.add_input(unit1.outputs().at(0));
    unit2.add_input(unit3.outputs().at(0));
    unit2.add_dependency(make_shared<UNIT_DD_ADD>(unit1));
    unit2.add_dependency(make_shared<UNIT_DD_NEG>(unit3));

    vector<shared_ptr<double>> inputs = {
      unit1.inputs()[0],
      unit1.inputs()[1],
      unit3.inputs()[0]
    };

    while (true) {
      for (auto &in : inputs) {
        std::cin >> *in;
        unit2.run_all();
        cout << "unit1:" << unit1 << endl;
        cout << "unit3:" << unit3 << endl;
        cout << "unit2:" << unit2 << endl;
      }
    }
  }
};

int main() {
  App app;
  app.start();
  return 0;
}
