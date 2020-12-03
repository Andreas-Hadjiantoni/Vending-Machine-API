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

#ifndef TESTS_H
#define TESTS_H

class vendingMachineTests {
public:
  // Constructor vendingMachine( currency curr, const std::vector<unsigned int>& initialQuantity ) :
  bool test_stored_coins_var_after_object_construction1();
  bool test_coins_var_after_object_construction1();
  bool test_exception_is_thrown_when_given_unsupported_currency();

  // Constructor vendingMachine( const std::map<coinValue, unsigned int>& initialCoins ):
  bool test_stored_coins_var_after_object_construction2();
  bool test_coins_var_after_object_construction2();

  // Function void addCoin( const coinValue coin ):
  bool test_storedCoins_var_after_addCoins_is_called_with_valid_data();
  bool test_storedCoins_var_after_addCoins_is_called_with_erronous_data();

  // Function const std::vector<coinValue>& computeChange( const float productCost ):
  bool test_return_val_of_computeChange_func_with_valid_data1();
  bool test_return_val_of_computeChange_func_with_valid_data2();
  bool test_return_val_of_computeChange_func_with_erronous_data1();
  bool test_return_val_of_computeChange_func_with_erronous_data2();
  bool test_storedCoins_var_after_computeChange_is_called_with_valid_data();
  bool test_storedCoins_var_after_computeChange_is_called_with_erronous_data();
};


#endif
