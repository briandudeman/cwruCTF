#include <iostream>
#include <algorithm>
// #include <string>
#include <assert.h>
// #include "BigInt.hpp"
#include "BinaryEncodingMasterFile.hpp"


using namespace std;

BigInt getNumSize(BigInt n) {
  BigInt size = n.to_string().size();
  return size;
}

BigInt getNumSizeStr(string n) {
  return (n.size());
}

/*
BigInt getNumSize(BigInt n) {
  if (n == 0) return 1; 
  
  int count = 0;
  n = abs(n);

  while (n > 0) {
      n /= 10;
      count++;
  }

  return count;
}
*/
BigInt ipow(BigInt base, BigInt exp) {
  /*
  int result = 1;
  for (;;)
  {
      if (exp & 1)
          result *= base;
      exp >>= 1;
      if (!exp)
          break;
      base *= base;
      
  }*/

  BigInt result = 1;
  for (BigInt i = 0; i < exp; i++) {
    result *= base;
  }

  return result;
}
/*
long long ipow(long long base, string exp)
{
    long long result = 1;
    long long expn = stoi(exp);
    for (;;)
    {
        if (expn & 1)
            result *= base;
        expn >>= 1;
        if (!expn)
            break;
        base *= base;
    }

    return result;
}
*/
string toBinary(BigInt num) {
    if (num == 0) return "0";  // Special case for 0

    string binary = "";
    while (num > 0) {
        binary += (num % 2 == 0 ? '0' : '1');  // Append the remainder (either '0' or '1')
        num /= 2;  // Divide the number by 2
    }

    // Reverse the string to get the correct binary order
    reverse(binary.begin(), binary.end());
    return binary;
}

string bigSubstr(string str, BigInt index, BigInt length) {
  string ret = "";
  while (index > 2147483647) {
    str = str.substr(2147483647);
    index -= 2147483647;
  }
  str = str.substr(index.to_int());
  while (length > 2147483647) {
    ret += str.substr(0,2147483647);
    length -= 2147483647;
  }
  ret += str.substr(0,length.to_int());

  return ret;
}

/*
string toBinary(int num) {
    if (num == 0) return "0";  // Special case for 0

    string binary = "";
    while (num > 0) {
        binary += (num % 2 == 0 ? '0' : '1');  // Append the remainder (either '0' or '1')
        num /= 2;  // Divide the number by 2
    }

    // Reverse the string to get the correct binary order
    reverse(binary.begin(), binary.end());
    return binary;
}
*/

BigInt toDecimal(string bin) {
  reverse(bin.begin(), bin.end());
  BigInt n = 0;
  // cout << "\t initial n: " << n << "\n";
  BigInt repeats = getNumSizeStr(bin);
  // cout << "\t repeats: " << repeats << "\n";
  
  for (BigInt i = 0; i < repeats; i++) {
    // cout << "\t nStart: " << n << "\n";
    n = n + bigSubstr(bin,i,1) * ipow(2,i);
    // cout << "\t i: " << i << "\n";
    // cout << "\t digit: " << bin.substr(i,1) << "\n";
    // cout << "\t power: " << ipow(2,i) << "\n";
    // cout << "\t nEnd: " << n << "\n";
  }

  return n;
}

string intCat(string n1, string n2) {
  return n1 + n2;
}

string lengthEncode(BigInt n) {
  BigInt sign;
  if (n < 0) {
    sign = 1;
    n = n * -1;
  } else {
    sign = 0;
  }

  string s = toBinary(sign);
  string num = toBinary(n);
  string c1 = toBinary(getNumSizeStr(num));
  string c2 = toBinary(getNumSizeStr(c1));
  string c3 = toBinary(getNumSizeStr(c2));
  string c4 = toBinary(getNumSizeStr(c3));
  string c5 = toBinary(getNumSizeStr(c4));
  
  if (c5 == "0") c5 = "00";
  if (c5 == "1") c5 = "01";

  // cout << s << "\n";
  // cout << num << "\n";
  // cout << c1 << "\n";
  // cout << c2 << "\n";
  // cout << c3 << "\n";
  // cout << c4 << "\n";

  string whole;
  return whole.append(s).append(c5).append(c4).append(c3).append(c2).append(c1).append(num);
}

// This is for encoding BigInts that might drop the leading zero
// e.g. when the 'int' was really a list or map
string lengthEncodeStr(BigInt n) {
  BigInt sign;
  if (n < 0) {
    sign = 1;
    n = n * -1;
  } else {
    sign = 0;
  }

  string s = toBinary(sign);
  string num = toBinary(n);
  num = intCat("0",num);
  string c1 = toBinary(getNumSizeStr(num));
  string c2 = toBinary(getNumSizeStr(c1));
  string c3 = toBinary(getNumSizeStr(c2));
  string c4 = toBinary(getNumSizeStr(c3));
  string c5 = toBinary(getNumSizeStr(c4));
  
  if (c5 == "0") c5 = "00";
  if (c5 == "1") c5 = "01";

  // cout << s << "\n";
  // cout << num << "\n";
  // cout << c1 << "\n";
  // cout << c2 << "\n";
  // cout << c3 << "\n";
  // cout << c4 << "\n";

  string whole;
  return whole.append(s).append(c5).append(c4).append(c3).append(c2).append(c1).append(num);
}

BigInt lengthDecode(string s) {
  // cout << getNumSizeStr(s) << "\n";
  
  string examined = s.substr(0,1);
  BigInt sign = stoi(examined);

  examined = s.substr(1,2);
  BigInt c5 = toDecimal(examined);
  // cout << "c5: " << c5 << "\n";

  examined = bigSubstr(s,3,c5);
  BigInt c4 = toDecimal(examined);
  // cout << "c4: " << c4 << "\n";

  examined = bigSubstr(s,3+c5,c4);
  BigInt c3 = toDecimal(examined);
  // cout << "c3: " << c3 << "\n";
  
  examined = bigSubstr(s,3+c5+c4,c3);
  BigInt c2 = toDecimal(examined);
  // cout << "c2: " << c2 << "\n";
  
  examined = bigSubstr(s,3+c5+c4+c3,c2);
  BigInt c1 = toDecimal(examined);
  // cout << "c1: " << c1 << "\n";
  
  examined = bigSubstr(s,3+c5+c4+c3+c2,c1);
  BigInt n = toDecimal(examined);
  // cout << "n: " << n << "\n";

  if (sign == 0) {
    sign = 1;
  } else {
    sign = -1;
  }

  return sign * n;
}


// struct dual_t {
//   BigInt val;
//   string remainder;
// };


dual_t lengthDecodeLeftmostValue(string s) {
  // cout << "\n\t\t\ts: " << s << "\n";
  string examined = s.substr(0,1);

  BigInt sign = stoi(examined);
  examined = s.substr(1,2);
  BigInt c5 = toDecimal(examined);
  examined = bigSubstr(s,3,c5);
  BigInt c4 = toDecimal(examined);
  examined = bigSubstr(s,3+c5,c4);
  BigInt c3 = toDecimal(examined);
  examined = bigSubstr(s,3+c5+c4,c3);
  BigInt c2 = toDecimal(examined);
  examined = bigSubstr(s,3+c5+c4+c3,c2);
  BigInt c1 = toDecimal(examined);
  examined = bigSubstr(s,3+c5+c4+c3+c2,c1);
  BigInt n = toDecimal(examined);

  if (sign == 0) {
    sign = 1;
  } else {
    sign = -1;
  }

  BigInt dSize = 3+c5+c4+c3+c2+c1;
  BigInt sSize = getNumSizeStr(s);
  // cout << "dSize: " << dSize << " sSize-dSize: " << sSize-dSize << "\n";
  BigInt vl = sign * n;
  string rmndr = bigSubstr(s,dSize,sSize-dSize);
  // cout << rmndr << "\n";
  dual_t ret = {vl,rmndr};
  return ret;
}

string newIntList() {
  return "00111110";
}

BigInt intListLen(string L) {
  dual_t t = lengthDecodeLeftmostValue(L);
  return t.val;
}

BigInt intListGet(string L, BigInt i) {
  if (i >= intListLen(L) || i < 0) throw invalid_argument("index out of range\n");
  // cout << "\n\t\t\t\t i: " << i << "\n";
  BigInt currIndex = -1;
  dual_t t;
  while (currIndex <= i) {
    t = lengthDecodeLeftmostValue(L);
    L = t.remainder;
    // cout << "\n\t\t\t t.val: " << t.val << "\n";
    // cout << "\n\t\t\t t.rem: " << t.remainder << "\n";
    currIndex += 1;
  }

  return t.val;
}

string intListSet(string L, BigInt i, BigInt v) {
  if (i >= intListLen(L) || i < 0) throw invalid_argument("index out of range\n");

  dual_t t = lengthDecodeLeftmostValue(L);
  
  string reEnc = lengthEncode(t.val);
  string firstListPart = reEnc;
  t = lengthDecodeLeftmostValue(t.remainder);
  BigInt currIndex = 0;
  
  while (currIndex < i) {
    reEnc = lengthEncode(t.val);
    firstListPart = intCat(firstListPart, reEnc);
    t = lengthDecodeLeftmostValue(t.remainder);
    currIndex += 1;
  }

  string repl = lengthEncode(v);
  string right = intCat(repl,t.remainder);
  string ret = intCat(firstListPart,right);

  return ret;
}


string intListSetStr(string L, BigInt i, string v) {
  if (i >= intListLen(L) || i < 0) throw invalid_argument("index out of range\n");

  dual_t t = lengthDecodeLeftmostValue(L);
  
  string reEnc = lengthEncode(t.val);
  string firstListPart = reEnc;
  t = lengthDecodeLeftmostValue(t.remainder);
  BigInt currIndex = 0;
  
  while (currIndex < i) {
    reEnc = lengthEncode(t.val);
    firstListPart = intCat(firstListPart, reEnc);
    t = lengthDecodeLeftmostValue(t.remainder);
    currIndex += 1;
  }

  // string repl = lengthEncode(v);
  string right = intCat(v,t.remainder);
  string ret = intCat(firstListPart,right);

  return ret;
}

string intListAppend(string L, BigInt v) {
  string inL = L;
  dual_t t = lengthDecodeLeftmostValue(inL);
  string len = lengthEncode(t.val + 1);
  
  string appnd = lengthEncode(v);
  string right = intCat(t.remainder,appnd);
  string ret = intCat(len,right);

  return ret;
}

string intListAppendStr(string L, string v) {
  string inL = L;
  dual_t t = lengthDecodeLeftmostValue(inL);
  string len = lengthEncode(t.val + 1);
  
  // string appnd = lengthEncode(v);
  string right = intCat(t.remainder,v);
  string ret = intCat(len,right);

  return ret;
}

dual_t intListPop(string L) {
  BigInt len = intListLen(L);
  dual_t t = lengthDecodeLeftmostValue(L);
  string newL = lengthEncode(t.val - 1);

  string curr;
  BigInt currIndex = 0;
  while (currIndex < len - 1) {
    t = lengthDecodeLeftmostValue(t.remainder);
    curr = lengthEncode(t.val);
    newL = intCat(newL, curr);
    currIndex += 1;
  }

  dual_t ret = {lengthDecode(t.remainder),newL};
  return ret;
}

string newIntSet() {
  return "00111110";
}

bool intSetContains(string s, BigInt v) {
  if (intListLen(s) == 0) return false;
  dual_t t = intListPop(s);
  while (v != t.val) {
    if (intListLen(t.remainder) == 0) return false;
    t = intListPop(t.remainder);
  }
  return true;
}

string intSetAdd(string s, BigInt v) {
  if (intSetContains(s, v)) return s;
  return intListAppend(s, v);
}

string encodeString(string s) {
  string charList = newIntList();
  BigInt asciiChar;
  char character;
  for (BigInt i = 0; i < s.length(); i++) {
    character = bigSubstr(s,i,1).c_str()[0];
    asciiChar = int(character);
    charList = intListAppend(charList, asciiChar);
  }
  return charList;
}

string decodeString(string s) {
  dual_t t = lengthDecodeLeftmostValue(s);
  string returnString = "";
  
  for (BigInt i = 0; i < t.val; i++) {
    returnString += char(intListGet(s, i).to_int());
  }
  return returnString;
}

string newIntMap() {
  return "00111110";
}

bool intMapContains(string m, BigInt key) {
  if (m == "00111110") return false;
  dual_t t = lengthDecodeLeftmostValue(m);
  
  for (BigInt i = 0; i < t.val; i += 2) {
    if (intListGet(m,i) == key)
      return true;
  }
  return false;
}

BigInt intMapGet(string m, BigInt key) {
  if (!intMapContains(m, key)) throw invalid_argument("no such key\n");

  dual_t t = lengthDecodeLeftmostValue(m);

  for (BigInt i = 0; i < t.val; i += 2) {
    if (intListGet(m, i) == key) {
      // cout << "\n\t\tm:" << m << "\n";
      return intListGet(m, i+1);
    }
  }
  throw invalid_argument("no such key\n");
}

string intMapSet(string m, BigInt key, BigInt value) {
  if (!intMapContains(m, key)) {
    m = intListAppend(m, key);
    m = intListAppend(m, value);
    return m;
  }

  dual_t t = lengthDecodeLeftmostValue(m);

  for (BigInt i = 0; i < t.val; i += 2) {
    if (intListGet(m, i) == key) {
      return intListSet(m, i+1, value);
    }
  }
  throw invalid_argument("what just happened\n");
}

string intMapSetStr(string m, BigInt key, string value) {
  if (!intMapContains(m, key)) {
    m = intListAppend(m, key);
    m = intListAppendStr(m, value);
    return m;
  }

  dual_t t = lengthDecodeLeftmostValue(m);

  for (BigInt i = 0; i < t.val; i += 2) {
    if (intListGet(m, i) == key) {
      return intListSetStr(m, i+1, value);
    }
  }
  throw invalid_argument("what just happened\n");
}

string newIntFSM() {
  return "010101010101001010111001000001111100101011100100000111110";
}


// struct mapSet_t {
//   string map;
//   string set;
// };


mapSet_t separateFSM(string fsm) {
  dual_t t = lengthDecodeLeftmostValue(fsm); // Gets rid of the length 2 prefix of all FSMs
  BigInt fsmLength = getNumSizeStr(t.remainder); // Gets the raw length of the entire FSM except the 2 prefix
  string restOfFsm = t.remainder;
  // cout << "\tfsmLength: " << fsmLength << "\n";
  // cout << "\trestOfFsm: " << restOfFsm << "\n";

  t = lengthDecodeLeftmostValue(intCat("0",intCat("10",bigSubstr(t.remainder,1,fsmLength-1)))); // t.remainder.substr(1,fsmLength-1))));
  BigInt mapLength = t.val;                            
  string restOfFsm2 = t.remainder;
  // cout << "\tmapLength: " << mapLength << "\n";
  // cout << "\trestOfFsm2: " << restOfFsm2 << "\n";

  string stateMap = bigSubstr(restOfFsm2,0,mapLength); // restOfFsm2.substr(0,mapLength);
  string stateSetWLen = bigSubstr(restOfFsm2,mapLength,getNumSizeStr(restOfFsm2)-mapLength); // restOfFsm2.substr(mapLength, getNumSizeStr(restOfFsm2)-mapLength));
  // cout << "\tstateMap: " << stateMap << "\n";
  // cout << "\tstateSetWLen: " << stateSetWLen << "\n";

  t = lengthDecodeLeftmostValue(intCat("0",intCat("10",bigSubstr(stateSetWLen,1,getNumSizeStr(stateSetWLen)-1)))); // stateSetWLen.substr(1,getNumSizeStr(stateSetWLen)-1)
  BigInt setLength = t.val;
  string lastOfFsm = t.remainder;
  // cout << "\tsetLength: " << setLength << "\n";
  // cout << "\tlastOfFsm: " << lastOfFsm << "\n";

  string stateSet = bigSubstr(lastOfFsm,0,setLength); // lastOfFsm.substr(0, setLength);
  // cout << "\tstateSet: " << stateSet << "\n";

  mapSet_t ret = {stateMap, stateSet};
  return ret;
}

bool isAcceptingState(string fsm, BigInt state) {
  mapSet_t f = separateFSM(fsm);
  return intSetContains(f.set, state);
}

string addAcceptingState(string fsm, BigInt state) {
  if (isAcceptingState(fsm, state)) return fsm;

  mapSet_t f = separateFSM(fsm);
  string outerMap = f.map;
  string stateSet = f.set;

  stateSet = intSetAdd(stateSet, state);
  stateSet = intCat("0",intCat(lengthEncode(getNumSizeStr(stateSet)).substr(3),stateSet));

  outerMap = intCat("0",intCat(lengthEncode(getNumSizeStr(outerMap)).substr(3),outerMap));

  return intCat("0101010101010",intCat(outerMap,stateSet));
}

BigInt getTransition(string fsm, BigInt fromState, BigInt digit) {
  mapSet_t f = separateFSM(fsm);
  // cout << "\n\tfsm:" << fsm << "\n";
  // cout << "\n\tf.map:" << f.map << "\n";

  if (!intMapContains(f.map, fromState)) throw invalid_argument("no such transition\n");
  // cout << "\n\tintMapGet: " << intMapGet(f.map, fromState) << "\n";
  string innerMap = lengthEncodeStr(intMapGet(f.map, fromState));
  // cout << "\n\tinnerMap1: " << innerMap << "\n";
  innerMap = intCat("0",intCat("10",innerMap.substr(1)));
  // cout << "\n\tinnerMap2: " << innerMap << "\n";
  dual_t t = lengthDecodeLeftmostValue(innerMap);
  innerMap = t.remainder;
  // cout << "\n\tinnerMap3: " << innerMap << "\n";
  // cout << "\n\tdigit: " << digit << "\n";
  if (!intMapContains(innerMap, digit)) throw invalid_argument("no such transition\n");

  return intMapGet(innerMap, digit);
}
// 010101010101001010101011100010101111010100101010101010100101010101110101010101011110
//                            010101111010100110101010101001010101011101010101010111100

string setTransition(string fsm, BigInt fromState, BigInt digit, BigInt toState) {
  mapSet_t f = separateFSM(fsm);

  // cout << "\n\tf.map: " << f.map << "\n";

  string newInnerMap = newIntMap();
  newInnerMap = intMapSet(newInnerMap, digit, toState);
  
  string currInnerMap;
  if (intMapContains(f.map, fromState)) {
    // cout << "\n\tif'ed";
    // cout << "\n\t\tf.map: " << f.map;
    // cout << "\n\t\tfromState: " << fromState;
    currInnerMap = lengthEncodeStr(intMapGet(f.map, fromState));
    currInnerMap = intCat("0",intCat("10",currInnerMap.substr(1)));
    // cout << "\n\t currInnerMap1: " << currInnerMap;
    currInnerMap = lengthDecodeLeftmostValue(currInnerMap).remainder;
    // cout << "\n\t currInnerMap2: " << currInnerMap;
    currInnerMap = intMapSet(currInnerMap, digit, toState);
  } else {
    // cout << "\n\telse'd";
    currInnerMap = newInnerMap;
  }
  // cout << "\tcurrInnerMap: " << currInnerMap << "\n";
  
  string innerMapLen = lengthEncode(getNumSizeStr(currInnerMap));
  string modifiedInnerLen = intCat("0",intCat(innerMapLen.substr(3),currInnerMap));


  // cout << "\tmodifiedInnerLen: " << modifiedInnerLen << "\n\n";
  // cout << "\tinnerMapLen: " << innerMapLen << "\n";
  
  // cout << "\tUnencodedinnerMapLen: " << getNumSizeStr(currInnerMap) << "\n";

  // cout << "\tlengthDecodedMIL: " << lengthDecode(modifiedInnerLen) << "\n";

  string outerMap = intMapSetStr(f.map, fromState, modifiedInnerLen);

  string outerMapNewLen = lengthEncode(getNumSizeStr(outerMap));
  outerMapNewLen = intCat("0",outerMapNewLen.substr(3));

  string stateSetLen = lengthEncode(getNumSizeStr(f.set));
  stateSetLen = intCat("0",stateSetLen.substr(3));

  // cout <<"\n\touterMapNewLen: " << outerMapNewLen << "\n";
  // cout << "\tUnencodedMapNewLen: " << getNumSizeStr(outerMap) << "\n";
  // cout <<"\touterMap: " << outerMap << "\n";
  // cout <<"\tstateSetLen: " << stateSetLen << "\n";
  // cout <<"\tf.set: " << f.set << "\n\n";

  return intCat("0101010101010",intCat(outerMapNewLen,intCat(outerMap, intCat(stateSetLen,f.set))));
}

bool accepts(string fsm, string inputValue) {
  BigInt currState = 1;
  BigInt repeats = getNumSizeStr(inputValue);

  // cout << "\n";
  for (BigInt i = 0; i < repeats; i++) {
    BigInt transition = bigSubstr(inputValue,0,1);
    // cout << "\ttransition: " << transition << "\n";
    inputValue = inputValue.substr(1);
    // cout << "\tinputValue: " << inputValue << "\n";
    try { currState = getTransition(fsm, currState, transition); }
    catch(const exception& e0) { return false; }
  }
  // cout << "Didnt throw error\n";
  // cout << "currState: " << currState << "\n";
  return isAcceptingState(fsm, currState);
}

string states(string fsm, string inputValue) {
  BigInt currState = 1;
  BigInt repeats = getNumSizeStr(inputValue);
  string stateList = newIntList();
  stateList = intListAppend(stateList, currState);

  for (BigInt i = 0; i < repeats; i++) {
    BigInt transition = bigSubstr(inputValue,0,1);
    inputValue = inputValue.substr(1);
    try { currState = getTransition(fsm, currState, transition); }
    catch(const exception& e0) { throw invalid_argument("no such transition\n"); }
    
    stateList = intListAppend(stateList, currState);
  }

  return stateList;
}

// #################################################
// Test Functions
// #################################################

void testLengthEncode() {
  cout << "Testing lengthEncode()... ";
  assert(lengthEncode(789) == "010101110010101100010101");
  assert(lengthEncode(-789) == "110101110010101100010101");
  assert(lengthEncode(1234512345) == "0101011101111111001001100101010010100111011001");
  assert(lengthEncode(-1234512345) == "1101011101111111001001100101010010100111011001");
  assert(lengthEncode(0) == "00111110");
  cout << "Passed!\n";
}

void testLengthDecode() {
  cout << "Testing lengthDecode()... ";
  string s = "010101110010101100010101";
  assert(lengthDecode(s) == 789);
  s = "1110101110010101100010101";
  assert(lengthDecode(s) == -789);
  s = "0101011101111111001001100101010010100111011001";
  assert(lengthDecode(s) == 1234512345);
  s = "1101011101111111001001100101010010100111011001";
  assert(lengthDecode(s) == -1234512345);
  s = "00111110";
  assert(lengthDecode(s) == 0);
  cout << "Passed!\n";
}

void testLengthDecodeLeftmostValue() {
  cout << "Testing lengthDecodeLeftmostValue()... ";
  string s = "0101010101010010101010101101010101011100";
  dual_t t = lengthDecodeLeftmostValue(s);
  assert(t.val == 2);
  assert(t.remainder == "010101010101101010101011100");

  s = "01010101111010001001010101011101";
  t = lengthDecodeLeftmostValue(s);
  assert(t.val == 34);
  assert(t.remainder == "01010101011101");

  s = "01010101010100011111000111110";
  t = lengthDecodeLeftmostValue(s);
  assert(t.val == 2);
  assert(t.remainder == "0011111000111110");

  s = "0011111000111110";
  t = lengthDecodeLeftmostValue(s);
  assert(t.val == 0);
  assert(t.remainder == "00111110");
  cout << "Passed!\n";
}

void testIntList() {
  cout << "Testing intList functions... ";
  string a1 = newIntList();
  string s = "";
  assert(a1 == "00111110"); // length-encoded 0
  assert(intListLen(a1) == 0);
  
  try { s = intListGet(a1, 0).to_string(); }
  catch(const exception& e1) {
    assert(string(e1.what()) == "index out of range\n");
  }

  a1 = intListAppend(a1, 42);
  assert(a1 == "00111111010101011110101010"); //# [1, 42]
  assert(intListLen(a1) == 1);;
  assert(intListGet(a1, 0) == 42);

  try { s = intListGet(a1, 1).to_string(); }
  catch(const exception& e2) {
    assert(string(e2.what()) == "index out of range\n");
  }
  try { s = intListSet(a1, 1, 99); }
  catch(const exception& e3) {
    assert(string(e3.what()) == "index out of range\n");
  }

  a1 = intListSet(a1, 0, 567);
  assert(a1 == "00111111010101110010101000110111"); // [1, 567]
  assert(intListLen(a1) == 1);
  assert(intListGet(a1, 0) == 567);

  a1 = intListAppend(a1, 8888);
  a1 = intListSet(a1, 0, 9);
  assert(a1 == "010101010101001010101110010010101011100111010001010111000"); // [2, 9, 8888]
  assert(intListLen(a1) == 2);
  assert(intListGet(a1, 0) == 9);
  assert(intListGet(a1, 1) == 8888);

  dual_t a1Pop = intListPop(a1);
  a1 = a1Pop.remainder;
  BigInt poppedValue = a1Pop.val;
  assert(poppedValue == 8888);
  assert(a1 == "001111110101010111001001"); // [1, 9]
  assert(intListLen(a1) == 1);
  assert(intListGet(a1, 0) == 9);

  a1Pop = intListPop(a1Pop.remainder);
  a1 = a1Pop.remainder;
  poppedValue = a1Pop.val;
  assert(intListLen(a1) == 0);
  assert(poppedValue == 9);

  // a1Pop = intListPop(a1Pop.remainder);
  
  try { s = intListGet(a1, 1).to_string(); }
  catch(const exception& e4) { 
    assert(string(e4.what()) == "index out of range\n");
  }

  string a2 = newIntList();
  a2 = intListAppend(a2, 0);
  assert(a2 == "0011111100111110");
  a2 = intListAppend(a2, 0);
  assert(a2 == "01010101010100011111000111110");
  cout << "Passed!\n";
}

void testIntSet() {
  cout << "Testing intSet functions... ";
  string s = newIntSet();
  assert(s == "00111110"); // [ 0 ]
  assert(intSetContains(s, 42) == false);
  s = intSetAdd(s, 42);
  assert(s == "00111111010101011110101010"); // [1, 42]
  assert(intSetContains(s, 42) == true);
  s = intSetAdd(s, 42); // multiple adds --> still just one
  assert(s == "00111111010101011110101010"); // [1, 42]
  assert(intSetContains(s, 42) == true);
  assert(intSetContains(s, 1) == false);
  cout << "Passed!\n";
}

void testEncodeDecodeStrings() {
  cout << "Testing encodeString and decodeString... ";
  assert(encodeString("A") == "001111110101010111111000001"); // [1, 65]
  assert(encodeString("f") == "001111110101010111111100110"); // [1, 102]
  assert(encodeString("3") == "00111111010101011110110011"); // [1, 51]
  assert(encodeString("!") == "00111111010101011110100001"); // [1, 33]
  assert(encodeString("Af3!") == "0101010101110001010101111110000010101010111111100110010101011110110011010101011110100001"); // [4,65,102,51,33]
  assert(decodeString("001111110101010111111000001") == "A"); 
  assert(decodeString("0101010101110001010101111110000010101010111111100110010101011110110011010101011110100001") == "Af3!");
  assert(decodeString(encodeString("WOW!!!")) == "WOW!!!");
  cout << "Passed!\n";
}

void testIntMap() {
    cout << "Testing intMap functions... ";
    BigInt test;
    
    string m = newIntMap();
    assert(m == "00111110"); // [ 0 ]
    assert(intMapContains(m, 42) == false);
    
    try { test = intMapGet(m, 42); }
    catch(const exception& e5) {
      assert(string(e5.what()) == "no such key\n");
    }
    
    m = intMapSet(m, 42, 73);
    assert(m == "01010101010100101010111101010100101010111111001001"); // [ 2, 42, 73 ]
    assert(intMapContains(m, 42) == true);
    assert(intMapGet(m, 42) == 73);
    m = intMapSet(m, 42, 98765);
    assert(m == "010101010101001010101111010101001010111011000111000000111001101"); // [ 2, 42, 98765 ]
    assert(intMapGet(m, 42) == 98765);
    m = intMapSet(m, 99, 0);
    assert(m == "0101010101110001010101111010101001010111011000111000000111001101010101011111110001100111110"); // [ 4, 42, 98765, 99, 0 ]
    assert(intMapGet(m, 42) == 98765);
    assert(intMapGet(m, 99) == 0);
    cout << "Passed!\n";
}

void testIntFSM() {
    cout << "Testing intFSM functions... ";
    string fsm = newIntFSM();
    assert(fsm == "010101010101001010111001000001111100101011100100000111110"); // [ empty stateMap, empty startStateSet ]
    assert(isAcceptingState(fsm, 1) == false);

    fsm = addAcceptingState(fsm, 1);
    assert(fsm == "010101010101001010111001000001111100101011101100000011111100111111");
    assert(isAcceptingState(fsm, 1) == true);
    
    try {getTransition(fsm, 0, 8); }
    catch(const exception& e6) {
      assert(string(e6.what()) == "no such transition\n");
    }
    
    fsm = setTransition(fsm, 4, 5, 6);
    // map[5] = 6: 111211151116
    // map[4] = (map[5] = 6):  111211141212111211151116
    // cout << "\n fsm -> " << fsm << " <- fsm\n";
    assert(fsm == "0101010101010010101111110101000101010101010010101010111000101011110101001010101010101001010101011101010101010111100101011101100000011111100111111");
//     Whole Outer Map: correct                  010101010101001010101011100010101111010100101010101010100101010101110101010101011110    
//     Whole Outer Map: correct                  010101010101001010101011100010101111010100101010101010100101010101110101010101011110
//     Unencoded Inner: notgood                                                                              1010101010100101010101110101010101011110
//     Enocded Inner M: notgood                                                              01010111101010001010101010100101010101110101010101011110
    /* 
    "0101010101010 <- outer list length
      01010111111010100 0101010101010 <- first item, map with raw length and number of contents
        01010101011100 <- fromState
        0101011110101001 0101010101010 01010101011101 01010101011110 <- inner map, with raw length, number of contents, and contents digit and toState
      010101110110000 00111111 00111111" <- second item, set with raw length and number of contents and contents
    */

    // cout << "1\n";
    assert(getTransition(fsm, 4, 5) == 6); // cout << "2\n";

    fsm = setTransition(fsm, 4, 7, 8); // cout << "3\n";
    fsm = setTransition(fsm, 5, 7, 9); // cout << "4\n";
    assert(getTransition(fsm, 4, 5) == 6); // cout << "5\n";
    assert(getTransition(fsm, 4, 7) == 8); // cout << "6\n";
    assert(getTransition(fsm, 5, 7) == 9); // cout << "7\n";
    
    fsm = newIntFSM();
    assert(fsm == "010101010101001010111001000001111100101011100100000111110"); // [ empty stateMap, empty startStateSet ]
    fsm = setTransition(fsm, 0, 5, 6);
    // cout << "\n fsm -> " << fsm << " <- fsm\n";
    // map[5] = 6: 111211151116
    // map[0] = (map[5] = 6):  111211101212111211151116      
    assert(fsm == "0101010101010010101111110011100101010101010001111100101011110101001010101010101001010101011101010101010111100101011100100000111110");
    /*             0101010101010010101111110011100101010101010001111100101011110101001010101010101001010101011101010101010111100101011100100000111110
    "0101010101010 <- outer list length
      01010111111001110 0101010101010 <- first item, map with raw length and number of contents
        00111110 <- fromState
        0101011110101001 0101010101010 01010101011101 01010101011110 <- inner map, with raw length, number of contents, and contents digit and toState
      0101011111 0111110
    */
    assert(getTransition(fsm, 0, 5) == 6);

    cout << "Passed!\n";
}

void testAccepts() {
    cout << "Testing accepts()... ";
    string fsm = newIntFSM();
    // fsm accepts 6*7+8
    fsm = addAcceptingState(fsm, 3);
    fsm = setTransition(fsm, 1, 6, 1); // 6* -> 1
    fsm = setTransition(fsm, 1, 7, 2); // 7 -> 2
    fsm = setTransition(fsm, 2, 7, 2); // 7* -> 2
    fsm = setTransition(fsm, 2, 8, 3); // 7* -> 3
    assert(accepts(fsm, "78") == true);
    assert(states(fsm, "78") == "01010101010110011111101010101010100101010101011"); // [1,2,3]
    assert(accepts(fsm, "678") == true);
    assert(states(fsm, "678") == "01010101011100001111110011111101010101010100101010101011"); // [1,1,2,3] 

    assert(accepts(fsm, "5") == false);
    assert(accepts(fsm, "788") == false);
    assert(accepts(fsm, "67") == false);
    assert(accepts(fsm, "666678") == true);
    assert(accepts(fsm, "66667777777777778") == true);
    assert(accepts(fsm, "7777777777778") == true);
    assert(accepts(fsm, "666677777777777788") == false);
    assert(accepts(fsm, "77777777777788") == false);
    assert(accepts(fsm, "7777777777778") == true);
    assert(accepts(fsm, "67777777777778") == true);
    cout << "Passed!\n";
}

// #################################################
// Main Function
// #################################################

/*
int main() {
  // string s = "01010101010100011111000111110";
  // cout << "Encoded representation of " << -9 << " is: " << lengthEncode(-9) << "\n";
  // cout << "Decoded representation of " << s << " is: " << lengthDecode(s) << "\n";
  // cout << "Encoded representation of " << 789 << " is: " << lengthEncode(789) << "\n" << "is (un)like " << "010101110010101100010101\n";
  // cout << "Encoded representation of " << 0 << " is: " << lengthEncode(0) << "\n";
  
  testLengthEncode();                                
  testLengthDecode();
  testLengthDecodeLeftmostValue();
  testIntList();
  testIntSet();
  testEncodeDecodeStrings();
  testIntMap();
  testIntFSM();
  testAccepts();

  // mapSet_t thing1 = separateFSM("010101010101001010111001000001111100101011100100000111110");
  // cout << "\n" << thing1.map << "\n";
  // cout << thing1.set << "\n";

  // string thing2 = addAcceptingState("010101010101001010111001000001111100101011100100000111110",5);
  // cout << "\n" << thing2 << "\n";

  return 0;
}
*/