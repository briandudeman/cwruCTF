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

dual_t genSquareMatrix(BigInt dim) {

  string twoDList = newIntList();
  string oneDList = newIntList();
  BigInt random;
  BigInt trace = 0;

  for(BigInt i = 0; i < dim; i++) {
    for(BigInt x = 0; x < dim; x++) {
      random = getRandom(1023);

      oneDList = intListAppend(oneDList,random);
      if (i == x) trace += random;
    }
    twoDList = intListAppendStr(twoDList,oneDList);
  }

  dual_t ret = {trace, twoDList};
  // cout << "\n\n\t\tTRACE: " << trace << "\n\n";
  return ret;
}

int main() {
  
  BigInt code = 1071095962;
  string input;
  BigInt x;
  dual_t problem = genSquareMatrix(2);
  string traceHolder = "trace";
  string clearHolder = "clear";
  string exampleList = newIntList();

  cout << "\nWelcome to the second Binary Encoding challenge!\n";
  cout << "If you haven't done the first challenge, you probably should.\n";
  
  cout << "\nThis time we will be encoding lists of integers.\n";
  cout << "To get the code, find the Trace of this random encoded 2x2 square 2D list-matrix:\n";

  cout << "\n\t" << problem.remainder << "\n\n";
  
  cout << "Again, you'll get to mess around with our list encoding function.\n";
  cout << "You can repeatedly enter any valid number to construct a list.\n";
  
  cout << "\nThat said, we won't let you try encoding 2D lists so easily.\n";
  cout << "Think hard about how we would represent a 2D list with a list that can only contain ints.\n";
  
  cout << "\nOnce you find the trace, we'll give you the code. Good luck!\n";

  cout << "\nHere is your empty list: " << exampleList << "\n";
  for(;;) {
    cout << "\n\tEnter a valid entry for a list, \'clear\' to restart, or \'trace\' to guess the trace: ";
    try {
      getline(cin, input);
      if (input == traceHolder) {
        cout << "\tEnter a valid guess for the trace: ";
        getline(cin, input);

        x = input;
        if (x == problem.val) { break; }
        else {  
          cout << "\n\tWe're sorry, but that is not the correct value of the trace.";
          cout << "\n\tIf you were previously building a list, it has been cleared.\n";
          exampleList = newIntList();
        }
      } else if (input == clearHolder) {
          exampleList = newIntList();
          cout << "\tHere is your cleared list: " << exampleList << "\n";
      } else { 
        x = input;
        exampleList = intListAppend(exampleList, x);
        cout << "\tHere is " << x << " encoded in your list: " << exampleList << "\n";
      }
    } catch (const exception e) {
      cout << "\tThat wasn't a valid input! Try again.\n";
    }
  }

  cout << "\n\nYou found the Trace! Here's the code: <cwruCTF-1071095962>" << endl;
  
  return 0;
}

