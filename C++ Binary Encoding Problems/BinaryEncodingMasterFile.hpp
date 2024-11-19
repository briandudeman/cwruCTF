#ifndef BINARY_ENCODING_MASTER_FILE_HPP
#define BINARY_ENCODING_MASTER_FILE_HPP

// #include <iostream>
// #include <algorithm>
#include <string>
// #include <assert.h>
#include "BigInt.hpp"

using namespace std;

BigInt getNumSize(BigInt n);

BigInt getNumSizeStr(string n);

BigInt ipow(BigInt base, BigInt exp);

string toBinary(BigInt num);

string bigSubstr(string str, BigInt index, BigInt length);

BigInt toDecimal(string bin);

string intCat(string n1, string n2);

string lengthEncode(BigInt n);

// This is for encoding BigInts that might drop the leading zero
// e.g. when the 'int' was really a list or map
string lengthEncodeStr(BigInt n);

BigInt lengthDecode(string s);

struct dual_t {
  BigInt val;
  string remainder;
};

dual_t lengthDecodeLeftmostValue(string s);

string newIntList();

BigInt intListLen(string L);

BigInt intListGet(string L, BigInt i);

string intListSet(string L, BigInt i, BigInt v);

string intListSetStr(string L, BigInt i, string v);

string intListAppend(string L, BigInt v);

string intListAppendStr(string L, string v);

dual_t intListPop(string L);

string newIntSet();

bool intSetContains(string s, BigInt v);

string intSetAdd(string s, BigInt v);

string encodeString(string s);

string decodeString(string s);

string newIntMap();

bool intMapContains(string m, BigInt key);

BigInt intMapGet(string m, BigInt key);

string intMapSet(string m, BigInt key, BigInt value);

string intMapSetStr(string m, BigInt key, string value);

string newIntFSM();

struct mapSet_t {
  string map;
  string set;
};

mapSet_t separateFSM(string fsm);

bool isAcceptingState(string fsm, BigInt state);

string addAcceptingState(string fsm, BigInt state);

BigInt getTransition(string fsm, BigInt fromState, BigInt digit);

string setTransition(string fsm, BigInt fromState, BigInt digit, BigInt toState);

bool accepts(string fsm, string inputValue);

string states(string fsm, string inputValue);

// #################################################
// Test Functions
// #################################################

void testLengthEncode();

void testLengthDecode();

void testLengthDecodeLeftmostValue();

void testIntList(); 

void testIntSet();

void testEncodeDecodeStrings();

void testIntMap();

void testIntFSM();

void testAccepts();

#endif // BINARY_ENCODING_MASTER_FILE_HPP

