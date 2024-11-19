#include "BinaryEncodingMasterFile.hpp"
#include <random>
#include <vector>
#include <assert.h>

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

struct genFSM_t {
  BigInt start;
  string fsm;
  string transitions;
  string states;
};

dual_t genFSM(BigInt dim, BigInt maxTs, BigInt accStates) {
  if (maxTs >= 9) maxTs = 9;
  if (maxTs < 0) maxTs *= -1;
  if (maxTs == 0) maxTs = 1;

  if(accStates >= dim) accStates = dim;
  if (accStates < 0) accStates *= -1;

  string fsm = newIntFSM();
  BigInt* stateList = new BigInt[dim.to_int()];
  BigInt randomFState;
  BigInt randomT;
  BigInt tCount;
  BigInt randomTState;
  BigInt startState;

  // cout << "\n\t\ENTERED\n";

  for (int x = 0; x < dim; x++) {
    randomFState = getRandom(1023);
    if (x == 0) randomFState = 1;
    stateList[x] = randomFState;
  }
  
  for (int i = 0; i < dim; i++) {
    // cout << "\tloop1\n";
    tCount = getRandom(maxTs.to_int()-1);
    if (tCount < 0) tCount *= -1;
    tCount += 1;
    
    if (i == 0) startState = stateList[i];

    for (int y = 0; y < tCount; y++) {
      //cout << "\tloop2\n";
      randomT = getRandom(9);
      if (randomT < 0) randomT *= -1;
      randomTState = getRandom(dim-1);
      if (randomTState < 0) randomTState *= -1;
      //cout << "\tb4\n";
      //cout << "\t\trandomT: " << randomT << "\n";
      //cout << "\t\trandomTState: " << randomTState.to_int() << "\n";
      //cout << "\t\tstateList: ";
      //for (int v = 0; v < dim.to_int(); v++) cout << stateList[v] << ", ";
      //out << "\n";
      //cout << "\t\tstateListAt: " << stateList[randomTState.to_int()] << "\n";
      // cout << "going...";
      // if (i == 0) cout << "\n\n\nRANDOMT: " << randomT << "\n\n\n";
      fsm = setTransition(fsm,stateList[i],randomT,stateList[randomTState.to_int()]);
      // cout << "aft...";
    }

    if (getRandom(1) == 0 || accStates == dim - i) {
      addAcceptingState(fsm,stateList[i]);
      accStates--;
    }
  }
  // cout << "\n\tLEAVING\n";
  dual_t ret = {startState, fsm};
  return ret;
}

mapSet_t genTraversal(string fsm, BigInt length, BigInt currState) {
  string transitions = "";
  string states = "";
  string potentialState = "";
  BigInt randomState;
  string seq;
  
  // cout << "\n\tENTERED2\n";

  random_device dev;
  mt19937 rng(dev());

  while (length > 0) {
    seq = "1234567890";
    shuffle(seq.begin(),seq.end(),rng);
    // cout << "\n\n" << seq << "\n\n";
    for (BigInt i = 0; i < 10; i++) {
      try {
        randomState = stoi(seq.substr(0,1));
        seq = seq.substr(1);

        potentialState = currState.to_string();
        // cout << "going with : " << randomState << "\n";
        currState = getTransition(fsm,currState,randomState);
        // cout << "Passed\n";
        transitions = intCat(transitions,i.to_string());
        states = intCat(states,potentialState);
        cout << "\n\tstates: " << states << "\n";
        length--;

        break;

      } catch (const exception& e0) {
        
        potentialState = "";
        // cout << "->" << string(e0.what()) << "<-\n";
        // cout << "\n^";
        assert(string(e0.what()) == "no such transition\n");
      }
    }
  }

  mapSet_t ret = {transitions, states};
  return ret;
}

int main() {
  cout << "Loading... (This may take a while)\n\n";
  BigInt code = 5938173054;
  string input;
  BigInt x;
  BigInt y;
  BigInt z;
  // cout << "START\n";
  // cout << "START\n";
  dual_t fsm = genFSM(6, 3, 2);
  // cout << "HI";
  mapSet_t traversal = genTraversal(fsm.remainder,10,fsm.val);
  // cout << "HELLO";
  string Transitions = traversal.map;
  string States = traversal.set;
  string exampleFSM = newIntFSM();
  dual_t helper;
  bool freeBool;
  cout << "\n\n STATES: " << States << "\n\n";

  cout << "\nWelcome to the fifth Binary Encoding challenge!\n";
  cout << "If you haven't done the prior challenges, you probably should.\n";
  
  cout << "\nNow we're going to work with our first big data structure: an Acceptor Finite State Machine.\n";
  cout << "As usual, our encoding can only handle integers.\n";
  cout << "For simplicity, each state may have at most 10 transitions, labeled by one digit, 0-9.\n";
  cout << "The labels for the states may be any integer.\n";
  cout << "It should be noted that this FSM is arbitrary, and does not represent anything of import.\n";

  cout << "\nBecause FSMs may be represented in many ways, we will give you a hand for this one.\n";
  cout << "There are many ways to represent FSMs, but here we use an intentionally more opaque method.\n";
  cout << "Our FSM is a list of two things, an \'outer\' map and a set.\n";
  cout << "The outer map maps start states to \'inner\' maps that maps transitions to end states. \n";
  cout << "The set contains accepting states. It is encoded the same as a list.\n";

  cout << "\n Now then. Here is a traversal, starting at the first state listed in the FSM.\n";

  cout << "\n\t" << Transitions << "\n\n";

  cout << "To get the code, traverse the FSM in this order, one digit at a time.\n";
  cout << "You must determine if the traversal ends on an accepting state, and all the states traversed.\n";
  cout << "For simplicity, the FSM will always have the state \'1\', from which all traversals start.\n";
  cout << "Here is the FSM:\n";

  cout << "\n\t" << fsm.remainder << "\n\n";
  
  cout << "Again, you'll get to mess around with our FSM encoding function.\n";
  cout << "We'll give you a wider range of options this time.\n";

  cout << "\nOnce you find path of the traversal, we'll give you the code. Good luck!\n";

  cout << "\nHere is your empty FSM: " << exampleFSM << "\n";
  for(;;) {
    cout << "\n\tEnter 'set\' to edit the FSM, \'get\' to examine it, \'clear\' to restart, or \'path\' to guess the path: ";
    getline(cin,input);

    if (input == "set") {
      cout << "\n\tEnter \'transition\' to set a transition, or \'state\' to set an accepting state: ";
      getline(cin,input);
      if (input == "transition") {
        try {
          cout << "\n\tEnter a valid state to transition from: ";
          getline(cin,input);
          x = input;

          cout << "\t\Enter a valid transition: ";
          getline(cin,input);
          y = input;

          cout << "\tEnter a valid state to transition to: ";
          getline(cin,input);
          z = input;

          exampleFSM = setTransition(exampleFSM,x,y,z);
          cout << "\tHere is " << x << "->" << z << " on " << y << " encoded in your FSM: " << exampleFSM << "\n";
          
        } catch (const exception& e1a) { 
          cout << "\tThat wasn't a valid input! Try again.\n";
        }
      } else if (input == "state") {
        try {
          cout << "\n\tEnter a valid state to be an accepting state: ";
          getline(cin,input);
          x = input;

          exampleFSM = addAcceptingState(exampleFSM,x);
          cout << "\tHere is " << x << " as an accepting state encoded in your FSM\n: " << exampleFSM << "\n";
          
        } catch (const exception& e1b) { 
          cout << "\tThat wasn't a valid input! Try again.\n";
        }
      } else {
        cout << "\tThat wasn't a valid input! Try again.\n";
      }
    } else if (input == "get") {
      cout << "\n\tEnter \'transition\' to check a transition, \'accepts\' to check an accepting state, or \'traversal\' to check a traversal: ";
      getline(cin,input);
      if (input == "transition") {
        try {
          cout << "\n\tEnter an existing state to transition from: ";
          getline(cin,input);
          x = input;

          cout << "\tEnter an existing transition from that state: ";
          getline(cin,input);
          y = input;

          cout << "\tHere is the state transitioned to from " << x << " on " << y << ": " << getTransition(exampleFSM,x,y) << "\n";
          
        } catch (const exception& e2a) { 
          cout << "\tThat wasn't a valid input! Try again.\n";
        }
      } else if (input == "accepts") {
        try {
          cout << "\n\tEnter a valid state to check if it is an accepting state: ";
          getline(cin,input);
          x = input;

          if (isAcceptingState(exampleFSM,x)) {
            cout << "\t" << x << " is an accepting state!\n";
          } else {
            cout << "\t" << x << " is not an accepting state.\n";
          }
          
        } catch (const exception& e2b) { 
          cout << "\tThat wasn't a valid input! Try again.\n";
        }
      } else if (input == "traversal") {
        try {
          cout << "\n\tEnter a valid sequence of traversals, such as \'302\': ";
          getline(cin,input);
          bool freeBool = accepts(exampleFSM,input);

          helper.remainder = input;
          input = states(exampleFSM,input);
          cout << "\t\'" << helper.remainder << "\' traverses the states ";
          helper = lengthDecodeLeftmostValue(input);
          y = helper.val;

          for (BigInt i = 0; i < y-1; i++) {
            helper = lengthDecodeLeftmostValue(helper.remainder);
            cout << helper.val << ", ";
          }
          helper = lengthDecodeLeftmostValue(helper.remainder);
          cout << "and " << helper.val;

          if (freeBool) {
            cout << ". It ends on an accepting state!\n";
          } else {
            cout  << ". It does not end on an accepting state.\n";
          }

        } catch (const exception& e2c) {
          cout << "\tThat wasn't a valid input! Try again.\n";
        }
      } else {
        cout << "\tThat wasn't a valid input! Try again.\n";;
      }
    } else if (input == "clear") {
        exampleFSM = newIntFSM();
        cout << "\tHere is your cleared FSM: " << exampleFSM << "\n";
    } else if (input == "path") {
        cout << "\tEnter a valid guess for the states in the path, with no commas or spaces: ";
        getline(cin, input);

        if (input == States) { break; }
        else {  
          cout << "\n\tWe're sorry, but that is not the correct path.";
          cout << "\n\tIf you were previously building an FSM, it has been cleared.\n";
          exampleFSM = newIntFSM();
        }
    } else {
      cout << "\tThat wasn't a valid input! Try again.\n";
    }
  }

  cout << "\n\nYou found the Path! Here's the code: <cwruCTF-5938173054>" << endl;
  
  return 0;
}

