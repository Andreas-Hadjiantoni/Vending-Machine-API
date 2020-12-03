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

#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <vector>
#include <map>
#include <set>

/**
 * Definition of the type used to represent coins.
 */
typedef float coinValue;

/**
 * @brief Definition of the currencies that can be used to initialise
 * a "vendingMachine" object
 */
enum currency {
  /// Coins used: {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00}
  GBP,
  /// Coins used: {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00}
  EUR,
  /// Coins used: {0.01, 0.05, 0.10, 0.25}
  USD
};

/**
 * A class containing the operations of the API.
 *
 * After initialization, objects of this class represent the state of
 * a vending machine wrt the coins contained in it. It supports
 * functionality to deposit coins by the user of the vending machine
 * and compute a collection of coins to be returned as change.
 */
class vendingMachine {
public:
  /**
   * @brief The default constructor is removed as we require a
   * collection of coins to be passed at initialisation.
   */
  vendingMachine() = delete;

  /**
   * Constructs "vendingMachine" objects using implemented currencies.
   *
   * One of the currencies defined in enum currency can be used to
   * initialise the vending machine. The state of the vending
   * machine when the constructor returns holds the quantity of each
   * coin of curr, given in initialQuantity.
   *
   * @param curr The currency that the vending macine will be using.
   *
   * @param initialQuantity The number of coins that the vending
   * machine will contain at initialisation. The elements of this
   * vector correspond to the quantities of coins of curr, starting
   * from the least valued coin.
   *
   * @throws
   *    vendingMachine::exceptions::unimplementedCurrencyException
   *    when curr is not one of the currencies defined in enum
   *    currency
   */
  vendingMachine( currency curr, const std::vector<unsigned int>& initialQuantity );

  /**
   * @brief Constructs "vendingMachine" objects by specifying the
   * coins to be used.
   *
   * This constructor is used to both specify the coin values of the
   * currency and the initial quantity of each coin.
   *
   * @param initialCoins defines the desired coin values of the
   * (unspecified) currency using its keyset. The value
   * initialCoins[c] is the number of c valued coins the machine will
   * be initialised with..
   */
  vendingMachine( const std::map<coinValue, unsigned int>& initialCoins );

  /**
   * Adds a coin to the collection of coins stored in the machine.
   *
   * @param coin Represents the value of the coin to be deposited. It
   * is expected that it contained in the set of coins specified
   * on initialization.
   *
   * @throws vendingMachine::exceptions::unsupportedCoinException
   *    is thrown when coin is not in the set of coins specified
   *    on initialization.
   */
  void addCoin( const coinValue coin );

  /**
   * Computes a collection of coins that sum up to "change".
   *
   * A collection that contails the least possible number of coins is
   * returned. Side-Effect: On success. it removes the coins from the
   * collection stored in the object.
   *
   * @param change the value that the returned collection should sum
   * up to.
   *
   * @returns an std::vector<coinValue> whose elements sum up to
   * "change".
   *
   * @throws vendingMachine::exceptions::notEnoughCoinsException is
   *    raised when such a collection could not be computed.
   */
  const std::vector<coinValue> computeChange( float change );

  /**
   * @brief A class that will be used for testing. It is given access
   * to private variables so that the state of "vendingMachine"
   * objects can be checked.
   */
  friend class vendingMachineTests;

  /**
   * @brief A list of possible exceptions that methods of this class
   * can throw.
   */
  enum exceptions {
    /// Thrown when passing an unsupported currency at initialization
    unimplementedCurrencyException,
    /// Thrown when depositing an invalid coin.
    unsupportedCoinException,
    /// Thrown when the required change could not be computed.
    notEnoughCoinsException
  };

private:
  /// Stores the quantity of each coin currently in the machine.
  std::map<coinValue, unsigned int> storedCoins;
  /// Stores every coin supported by this "vendingMachine" instance.
  std::set<coinValue> coins;
};

#endif
