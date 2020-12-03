# Vending Machine API

This is a simple API which supports basic operations for vending machines. It keeps track of the stored coins in the vending machine, allows for new coins to be deposited, and computes a collection of coins that sum up to a given 'change' value.

## Usage Instructions for Linux

### Setup

To be able to compile and run this program on a fresh Linux installation, execute:

````shell
$ apt update
$ apt install g++=4:8.3.0-1
````

### Compilation

To compile, execute:

````shell
$ g++ -std=c++11 *.cpp -o main
````

### Run tests

To run the tests and a small use-case defined in `main()`, execute:


````shell
$ ./main
````

## Design Choices

In this section we justify some design choices made and explain how some ambiguities in the specification were handled.

### Language chosen

Since this code will be run on vending machine hardware, we expect limited memory and speed. Hence, we rule out every language that does not compile to executable machine code. We choose C++, as it allows for object oriented code, and provides a great trade-off between speed and available abstraction mechanisms.

### Data structures used

To represent the set of accepted coins in an already initialized `vendingMachine` object, we use an `std::set<float>`. To represent the mapping from coins to the number of coins currently contained in the machine, we use `std::map<float, unsigned int>`.

The underlying implementation of `std::set` and `std::map` with balanced binary trees allow for logarithmic time insertion and lookup wrt the number of different coins accepted. Since we only have a constant number of accepted coins (e.g. Eight different coins for GBP), we can effectively lookup and insert items in constant time.

`std::unordered_set` and `std::unordered_map` were avoided since they have large constant factors and can have large memory requirements.

### Available currencies

The specification states that the company produces vending machines "currently for the UK", without specifying whether there are plans to expand to markets outside of the UK in the future.

Therefore, the API can handle coins of GBP and other major currencies(USD and EUR). The user can specify the desired currency as a parameter in a constructor. It also allows for any other (unspecified) currency to be used, provided that the user of the API will specify the values of the coins of said currency.

### Handling of errors

It is possible that the user of the API requests to deposit a coin that is not in the set of coins of the chosen/provided currency. It is also possible that the vending machine does not have enough coins that can sum up to the desired 'change' value. We handle both of these cases by raising the appropriate exceptions.
