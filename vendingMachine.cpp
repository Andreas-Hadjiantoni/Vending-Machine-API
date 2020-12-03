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
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <cassert>

vendingMachine::vendingMachine( currency curr, const std::vector<unsigned int>& initialQuantity ) {
  std::vector<coinValue> coins;

  // Check which of the implemented currencies will be used.
  switch ( curr ) {
    case GBP:
      coins = { 0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00 };
      break;

    case EUR:
      coins = { 0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00 };
      break;

    case USD:
      coins = { 0.01, 0.05, 0.10, 0.25 };
      break;

    default:
      std::cerr << "ERROR: Currency not implemented!" << std::endl;
      throw unimplementedCurrencyException;
      break;
  }

  assert( coins.size() == initialQuantity.size() );

  // Fill both private variables of this object
  for ( int i = 0; i < coins.size(); i++ )
    storedCoins[coins[i]] = initialQuantity[i];

  this->coins = std::set<coinValue>(coins.begin(), coins.end());
}

vendingMachine::vendingMachine( const std::map<coinValue, unsigned int>& initialCoins ):
  storedCoins(initialCoins) {

    // Fill coins set
    for ( auto coinPair : initialCoins )
      coins.emplace( coinPair.first );

  }

void vendingMachine::addCoin( const coinValue coin ) {
  // Coin not in coins set implies coin is invalid
  if ( coins.count( coin ) == 0 ) {
    std::cerr << "ERROR: VendingMachine::addCoin() was invoked with invalid parameters." << std::endl;
    throw unsupportedCoinException;
  } else
    storedCoins[coin]++;
}

const std::vector<coinValue> vendingMachine::computeChange( float change ) {
  std::vector<coinValue> result;

  // Use this instead of 0.0 due to float representation precision loss
  const float tolerance = 0.000001;

  // Consider largest coins first to populate "result"
  for ( auto it = coins.rbegin(); it != coins.rend(); it++ ) {
    coinValue coin = *it;
    while ( change - coin >= -tolerance && storedCoins[coin] > 0 )  {
      storedCoins[coin]--;
      change -= coin;
      result.push_back( coin );
    }
  }

  // From the loop above we know that change >= -tolerance
  if ( change < tolerance ) // We effectively check change == 0.0
    return result;

  // We haven't been able to find exact change
  for ( coinValue coin : result )
    storedCoins[coin]++;

  std::cerr << "ERROR: vendingMachine::computeChange() could not find enough coins for" << std::endl \
            << "ERROR: the requested change." << std::endl;
  throw notEnoughCoinsException;
}
