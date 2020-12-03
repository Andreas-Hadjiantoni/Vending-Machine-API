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
#include <map>
#include <iostream>

using namespace std;

vendingMachine buildVendMachine( vector<coinValue> coinValues, vector<unsigned int> coinQuantities ) {
  map<coinValue, unsigned int> initialCoins;

  for ( int i = 0; i < coinValues.size(); i++ ) {
    coinValue coin = coinValues[i];
    unsigned int quantity = coinQuantities[i];
    initialCoins[coin] = quantity;
  }

  return vendingMachine( initialCoins );
}

// Constructor vendingMachine( currency curr, const std::vector<unsigned int>& initialQuantity ) tests:

bool vendingMachineTests::test_stored_coins_var_after_object_construction1() {
  vector<coinValue> EURcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {20,   20,   20,   50,   50,   50,   100,  100};
  vendingMachine myVendMachine( EUR, coinQuantities );

  bool validState = true;

  for ( int i = 0; i < coinQuantities.size(); i++ ) {
    coinValue coin = EURcoinValues[i];

    if ( myVendMachine.storedCoins[coin] != coinQuantities[i] ) {
      validState = false;
      cout << "ERROR: Test test_stored_coins_var_after_object_construction1 failed." << endl;
      break;
    }
  }

  return validState;
}


//checks that coins variable is sorted and contains the expected elements
bool vendingMachineTests::test_coins_var_after_object_construction1() {
  vector<coinValue> USDcoinValues =     { 0.25, 0.10, 0.05, 0.01 };
  vector<unsigned int> coinQuantities = {20,   40,   80,   80 };

  vendingMachine myVendMachine( USD, coinQuantities );
  bool validState = true;

  if ( myVendMachine.coins.size() != USDcoinValues.size() ) {
    cout << "ERROR: Test test_coins_var_after_object_construction1 failed." << endl;
    return false;
  }

  for ( int i = 0; i < USDcoinValues.size(); i++ )
      if ( myVendMachine.coins.count( USDcoinValues[i] ) == 0 ) {
      validState = false;
      cout << "ERROR: Test test_coins_var_after_object_construction1 failed." << endl;
      break;
    }

  return validState;
}

bool vendingMachineTests::test_exception_is_thrown_when_given_unsupported_currency() {
  vector<unsigned int> coinQuantities = {20,   40,   80,   80 };
  currency YEN = currency(4);

  try {
    vendingMachine myVendMachine( YEN, coinQuantities );
  } catch( vendingMachine::exceptions e ) {
    if ( e == vendingMachine::exceptions::unimplementedCurrencyException )
      return true;
  }

  cout << "ERROR: Test test_exception_is_thrown_when_given_unsupported_currency failed." << endl;
  return false;
}

// Constructor vendingMachine( const std::map<coinValue, unsigned int>& initialCoins ) tests:

bool vendingMachineTests::test_stored_coins_var_after_object_construction2() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {20,   20,   20,   50,   50,   50,   100,  100};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );
  bool validState = true;

  for ( int i = 0; i < coinQuantities.size(); i++ ) {
    coinValue coin = GBPcoinValues[i];

    if ( myVendMachine.storedCoins[coin] != coinQuantities[i] ) {
      validState = false;
      cout << "ERROR: Test test_stored_coins_var_after_object_construction2 failed." << endl;
      break;
    }
  }

  return validState;
}

//checks that coins variable is sorted and contains the expected elements
bool vendingMachineTests::test_coins_var_after_object_construction2() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {20,   20,   20,   50,   50,   50,   100,  100};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );
  bool validState = true;

  if ( myVendMachine.coins.size() != GBPcoinValues.size() ) {
    cout << "ERROR: Test test_coins_var_after_object_construction2 failed." << endl;
    return false;
  }

  for ( int i = 0; i < GBPcoinValues.size(); i++ )
    if ( myVendMachine.coins.count( GBPcoinValues[i] ) == 0 ) {
      validState = false;
      cout << "ERROR: Test test_coins_var_after_object_construction2 failed." << endl;
      break;
    }

  return validState;
}

// Function void addCoin( const coinValue coin )

bool vendingMachineTests::test_storedCoins_var_after_addCoins_is_called_with_valid_data() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {20,   20,   20,   50,   50,   50,   100,  100};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  myVendMachine.addCoin( 0.10 );
  coinQuantities[3]++;

  myVendMachine.addCoin( 1.00 );
  coinQuantities[6]++;

  myVendMachine.addCoin( 2.00 );
  coinQuantities[7]++;

  bool validState = true;

  for ( int i = 0; i < coinQuantities.size(); i++ ) {
    coinValue coin = GBPcoinValues[i];

    if ( myVendMachine.storedCoins[coin] != coinQuantities[i] ) {
      validState = false;
      cout << "ERROR: Test test_storedCoins_var_after_addCoins_is_called_with_valid_data failed." << endl;
      break;
    }
  }

  return validState;
}

bool vendingMachineTests::test_storedCoins_var_after_addCoins_is_called_with_erronous_data() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {20,   20,   20,   50,   50,   50,   100,  100};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  try {
    myVendMachine.addCoin( 0.13 );
  } catch( vendingMachine::exceptions e ) {
    if ( e == myVendMachine.unsupportedCoinException )
      return true;
  }

  cout << "ERROR: Test test_storedCoins_var_after_addCoins_is_called_with_erronous_data failed." << endl;
  return false;
}

//Function const std::vector<coinValue>& computeChange( const float productCost )

bool vendingMachineTests::test_return_val_of_computeChange_func_with_valid_data1() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {20,   20,   20,   50,   50,   50,   100,  100};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  vector<coinValue> change = myVendMachine.computeChange( 3.26 );

  vector<coinValue> expectedChange = { 2.00, 1.00, 0.20, 0.05, 0.01 };

  bool validReturnValue = ( expectedChange == change );

  if ( !validReturnValue )
    cout << "ERROR: Test test_return_val_of_computeChange_func_with_valid_data1 failed." << endl;

  return validReturnValue;
}

bool vendingMachineTests::test_return_val_of_computeChange_func_with_valid_data2() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {20,   20,   20,   50,   50,   0,    0,    0};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  vector<coinValue> change = myVendMachine.computeChange( 3.26 );

  vector<coinValue> expectedChange(int(3.00 / 0.20), 0.20);
  expectedChange.push_back(0.20);
  expectedChange.push_back(0.05);
  expectedChange.push_back(0.01);

  bool validReturnValue = ( expectedChange == change );

  if ( !validReturnValue )
    cout << "ERROR: Test test_return_val_of_computeChange_func_with_valid_data2 failed." << endl;

  return validReturnValue;
}

// Maximum change we can give is 6.80, but we ask for 8.00
bool vendingMachineTests::test_return_val_of_computeChange_func_with_erronous_data1() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {10,   10,   10,   10,   5,    2,    1,    1};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  try {
    vector<coinValue> change = myVendMachine.computeChange( 8.00 );
  } catch ( vendingMachine::exceptions e ) {
    if ( e == myVendMachine.notEnoughCoinsException )
      return true;
  }

  cout << "ERROR: Test test_return_val_of_computeChange_func_with_erronous_data1 failed." << endl;

  return false;
}

// We cannot find exactly the change requested, but we could give more
bool vendingMachineTests::test_return_val_of_computeChange_func_with_erronous_data2() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {0,    0,    10,   10,   10,   10,   10,   10};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  try {
    vector<coinValue> change = myVendMachine.computeChange( 3.26 );
  } catch ( vendingMachine::exceptions e ) {
    if ( e == myVendMachine.notEnoughCoinsException )
      return true;
  }

  cout << "ERROR: Test test_return_val_of_computeChange_func_with_erronous_data2 failed." << endl;

  return false;
}

bool vendingMachineTests::test_storedCoins_var_after_computeChange_is_called_with_valid_data() {
  vector<coinValue> GBPcoinValues =          {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities =      {20,   20,   20,   50,   50,   50,   100,  100};
  vector<coinValue> expectedCoinQuantities = {19,   20,   19,   50,   49,   50,   99,   99};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  myVendMachine.computeChange( 3.26 );
  bool validState = true;

  for ( int i = 0; i < GBPcoinValues.size(); i++ ) {
    coinValue coin = GBPcoinValues[i];
    if ( myVendMachine.storedCoins[coin] != expectedCoinQuantities[i] ) {
      cout << "ERROR: Test test_storedCoins_var_after_computeChange_is_called_with_valid_data failed." << endl;
      validState = false;
      break;
    }
  }

  return validState;
}

bool vendingMachineTests::test_storedCoins_var_after_computeChange_is_called_with_erronous_data() {
  vector<coinValue> GBPcoinValues =     {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
  vector<unsigned int> coinQuantities = {0,    0,    10,   10,   10,   10,   10,   10};

  vendingMachine myVendMachine = buildVendMachine( GBPcoinValues, coinQuantities );

  try {
    vector<coinValue> change = myVendMachine.computeChange( 3.26 );
  } catch ( vendingMachine::exceptions e ) { }

  bool validState = true;

  for ( int i = 0; i < GBPcoinValues.size(); i++ ) {
    coinValue coin = GBPcoinValues[i];
    if ( myVendMachine.storedCoins[coin] != coinQuantities[i] ) {
      cout << "ERROR: Test test_storedCoins_var_after_computeChange_is_called_with_erronous_data failed." << endl;
      validState = false;
      break;
    }
  }

  return validState;
}
