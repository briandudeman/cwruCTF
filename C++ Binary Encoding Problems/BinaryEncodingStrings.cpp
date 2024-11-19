#include "BinaryEncodingMasterFile.hpp"

using namespace std;

int main() {

  string input;
  string answer = "<cwruCTF-8301735738>";

  cout << "\nWelcome to the third Binary Encoding challenge!\n";
  
  cout << "\nHere's the 10-digit code:\n";
  
  cout << "\n\t" << encodeString("<cwruCTF-8301735738>") << "\n\n";
  
  cout << "That's all we'll tell you; good luck!\n";
  
  cout << "\n(You can input your guess for the whole code; not necessary to solve the problem.)\n";

  for(;;) {
    cout << "\n\tEnter a valid a guess for the code: ";
    try {
      getline(cin, input);
    } catch (const exception e) {
      cout << "\tThat wasn't a valid input! Try again.\n";
    }
    
    if (input == answer) { break; }
    else { cout << "\n\tNope! Try again."; }
  }

  cout << "\n\nYou found the code! <cwruCTF-8301735738>" << endl;
  
  return 0;
}

