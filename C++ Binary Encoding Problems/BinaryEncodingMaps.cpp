#include "BinaryEncodingMasterFile.hpp"
#include <random>
#include <vector>

using namespace std;

BigInt getRandom(BigInt max) {
  if (max > INT_MAX) max = INT_MAX;
  int m = max.to_int();
  if (m < 0) m *= -1;

  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<mt19937::result_type> distNum(0,m);
  uniform_int_distribution<mt19937::result_type> distSign(0,1);

  int sign = 1;
  if (distSign(rng) == 1) sign = -1;

  BigInt ret = distNum(rng);

  return ret * sign;

}

dual_t genMap(BigInt dim) {

  string oneDMap = newIntMap();
  BigInt random;
  BigInt sum = 0;

  for(BigInt i = 1; i <= dim; i++) {
    random = getRandom(1023);

    oneDMap = intMapSet(oneDMap,i,random);
    
    if (i == 3) sum += random;
    if (i == 1) sum += random;
    if (i == 4) sum += random;
    if (i == 1) sum += random;
    if (i == 5) sum += random;
  }

  dual_t ret = {sum, oneDMap};
  // cout << "\n\n\t\tSUM: " << sum << "\n\n";
  return ret;
}

int main() {
  
  BigInt code = 9482048294;
  string input;
  BigInt x;
  BigInt y;
  dual_t problem = genMap(5);
  string sumHolder = "sum";
  string clearHolder = "clear";
  string exampleMap = newIntMap();

  cout << "\nWelcome to the fourth Binary Encoding challenge!\n";
  cout << "If you haven't done the second challenge, you probably should.\n";
  
  cout << "\nThis time we have an encoded map (dictionary) of integers to integers.\n";
  cout << "The 'password' to the map is the first 5 digits of pi.\n";
  cout << "To get the code, input the password to the keys of this random map and add the outputs:\n";

  cout << "\n\t" << problem.remainder << "\n\n";
  
  cout << "Again, you'll get to mess around with our map encoding function.\n";
  cout << "You can repeatedly enter any valid key and then value to construct a map.\n";

  cout << "\nOnce you find the sum, we'll give you the code. Good luck!\n";


  cout << "\nHere is your empty map: " << exampleMap << "\n";
  for(;;) {
    cout << "\n\tEnter a valid key for a map, \'clear\' to restart, or \'sum\' to guess the sum: ";
    try {
      getline(cin, input);
      if (input == sumHolder) {
        cout << "\tEnter a valid guess for the sum: ";
        getline(cin, input);

        x = input;
        if (x == problem.val) { break; }
        else {  
          cout << "\n\tWe're sorry, but that is not the correct value of the sum.";
          cout << "\n\tIf you were previously building a map, it has been cleared.\n";
          exampleMap = newIntMap();
        }
      } else if (input == clearHolder) {
          exampleMap = newIntMap();
          cout << "\tHere is your cleared map: " << exampleMap << "\n";
      } else { 
        x = input;
        for (;;) {
          try {
            cout << "\tEnter a valid value for a map: ";
            getline(cin, input);

            y = input;
            exampleMap = intMapSet(exampleMap, x, y);
            break;
          } catch (const exception e2) {
            cout << "\tThat wasn't a valid value input! Try again.\n";
          }
        }
        cout << "\tHere is " << x << "->" << y << " encoded in your map: " << exampleMap << "\n";
      }
    } catch (const exception e1) {
      cout << "\tThat wasn't a valid input! Try again.\n";
    }
  }

  cout << "\n\nYou found the Sum! Here's the code: <cwruCTF-9482048294>" << endl;
  
  return 0;
}

