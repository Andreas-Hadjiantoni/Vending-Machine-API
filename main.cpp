/*
 * Developed for the VMachine industries.
 * This product includes software developed by the VMachine industries.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "vendingMachine.h"
#include "tests.h"
#include <iostream>
#include <fstream>

using namespace std;

void runTests() {

  // Since we don't use a log class to hide the errors, we use the
  // following three lines:
  ofstream blackHole("/dev/null");
  auto cerrBuff = cerr.rdbuf();
  streambuf* errorBuffer = cerr.rdbuf(blackHole.rdbuf());

  vendingMachineTests tests;

  const int testCount = 13;
  int passedTests = 0;

  passedTests += int(tests.test_stored_coins_var_after_object_construction1());
  passedTests += int(tests.test_coins_var_after_object_construction1());
  passedTests += int(tests.test_exception_is_thrown_when_given_unsupported_currency());

  passedTests += int(tests.test_stored_coins_var_after_object_construction2());
  passedTests += int(tests.test_coins_var_after_object_construction2());

  passedTests += int(tests.test_storedCoins_var_after_addCoins_is_called_with_valid_data());
  passedTests += int(tests.test_storedCoins_var_after_addCoins_is_called_with_erronous_data());

  passedTests += int(tests.test_return_val_of_computeChange_func_with_valid_data1());
  passedTests += int(tests.test_return_val_of_computeChange_func_with_valid_data2());
  passedTests += int(tests.test_return_val_of_computeChange_func_with_erronous_data1());
  passedTests += int(tests.test_return_val_of_computeChange_func_with_erronous_data2());
  passedTests += int(tests.test_storedCoins_var_after_computeChange_is_called_with_valid_data());
  passedTests += int(tests.test_storedCoins_var_after_computeChange_is_called_with_erronous_data());

  std::cout << "Total tests passed: " << passedTests << " / " << testCount << '\n';
  cerr.rdbuf(cerrBuff);
}

int main() {

  runTests();

  std::cout << "=========================" << '\n';

  // Initialise vending Machine:
  vector<unsigned int> quantities = {20, 20, 20, 50, 50, 100, 100, 100};
  vendingMachine myMachine(GBP, quantities);

  // Assume a product costs £1.25
  // Someone gives a £2 coin => change should sum to 0.75p

  vector<coinValue> change = myMachine.computeChange( 0.75 );

  for ( auto coin : change )
    cout << coin << endl;

  return 0;
}
