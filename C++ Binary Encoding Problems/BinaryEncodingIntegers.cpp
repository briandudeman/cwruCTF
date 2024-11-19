#include "BinaryEncodingMasterFile.hpp"

using namespace std;

int main() {

  BigInt code = 3270985610;
  string input;
  BigInt x;


  cout << "\nWelcome to the first Binary Encoding challenge!\n";
  
  cout << "\nSince this is the first, we'll make this easy. Here's the 10-digit code:\n";
  
  cout << "\n\t<cwruCTF-" << lengthEncode(code) << ">\n\n";
  
  cout << "... Well, that's not 10 digits. It looks like it's been encoded; you'll have to decode it.\n";
  cout << "We'll give you a helping hand: you can test out our encoding function.\n";
  cout << "It can take any integer, positive or negative, of any length.\n";
  
  cout << "\n(If you input the correct code we'll let you know, though this is optional.)\n";

  for(;;) {
    cout << "\n\tEnter a valid number to encode: ";
    try {
      getline(cin, input);
      x = input;
      cout << "\tHere is " << x << " encoded: " << lengthEncode(x) << "\n";
    } catch (const exception e) {
      cout << "\tThat wasn't a valid input! Try again.\n";
    }
    
    if (x == 3270985610) break;
  }

  cout << "\n\nYou found the code! <cwruCTF-3270985610>" << endl;
  
  return 0;
}

