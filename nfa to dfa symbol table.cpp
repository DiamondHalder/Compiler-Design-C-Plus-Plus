#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct NFATransition {
    int currentState;          // NFA state
    char inputSymbol;
    vector<int> nextStates;    // Multiple next states
};

struct DFATransition {
    int currentState;          // DFA state
    char inputSymbol;
    int nextState;             // Single next state
};

// Global variables for NFA and DFA
vector<NFATransition> nfaTransitionTable;
unordered_map<string, int> dfaStateMap; // Maps string representation to DFA state ID
vector<DFATransition> dfaTransitionTable;
int dfaStateCounter = 0;

// Function to compute epsilon closure
unordered_set<int> epsilonClosure(int state) {
    unordered_set<int> closure;
    closure.insert(state);
    vector<int> stack = {state};

    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();

        for (const auto &transition : nfaTransitionTable) {
            if (transition.currentState == current && transition.inputSymbol == 'e') {
                for (int nextState : transition.nextStates) {
                    if (closure.insert(nextState).second) {
                        stack.push_back(nextState);
                    }
                }
            }
        }
    }
    return closure;
}

// Function to generate unique state names
string stateName(const unordered_set<int> &stateSet) {
    vector<int> states(stateSet.begin(), stateSet.end());
    sort(states.begin(), states.end());
    string name = "{";
    for (int s : states) {
        name += to_string(s) + ",";
    }
    name.pop_back();
    name += "}";
    return name;
}

// Function to convert NFA to DFA
void convertNFAtoDFA() {
    unordered_set<int> initialState = epsilonClosure(0);
    string initialStateName = stateName(initialState);

    dfaStateMap[initialStateName] = dfaStateCounter++;
    vector<unordered_set<int>> unprocessedDFAStates = {initialState};

    while (!unprocessedDFAStates.empty()) {
        unordered_set<int> currentDFAState = unprocessedDFAStates.back();
        unprocessedDFAStates.pop_back();
        string currentDFAStateName = stateName(currentDFAState);

        for (char symbol : {'a', 'b'}) {
            unordered_set<int> nextStateSet;

            for (int state : currentDFAState) {
                for (const auto &transition : nfaTransitionTable) {
                    if (transition.currentState == state && transition.inputSymbol == symbol) {
                        for (int nextState : transition.nextStates) {
                            auto closure = epsilonClosure(nextState);
                            nextStateSet.insert(closure.begin(), closure.end());
                        }
                    }
                }
            }

            if (!nextStateSet.empty()) {
                string nextStateName = stateName(nextStateSet);

                if (dfaStateMap.find(nextStateName) == dfaStateMap.end()) {
                    dfaStateMap[nextStateName] = dfaStateCounter++;
                    unprocessedDFAStates.push_back(nextStateSet);
                }

                dfaTransitionTable.push_back({dfaStateMap[currentDFAStateName], symbol, dfaStateMap[nextStateName]});
            }
        }
    }
}

int main() {
    // NFA transition table setup
    nfaTransitionTable.push_back({0, 'e', {6, 7}});
    nfaTransitionTable.push_back({1, 'a', {2}});
    nfaTransitionTable.push_back({2, 'e', {5}});
    nfaTransitionTable.push_back({3, 'b', {4}});
    nfaTransitionTable.push_back({4, 'e', {5}});
    nfaTransitionTable.push_back({5, 'e', {6, 7}});
    nfaTransitionTable.push_back({6, 'e', {1, 3}});

    cout << "\n\tNFA Transition Table\n";
    cout << "_________________________________________\n";
    cout << "Current State | Input | Next States\n";
    cout << "_________________________________________\n";
    for (const auto &transition : nfaTransitionTable) {
        cout << "      q[" << transition.currentState << "]      |   "
             << transition.inputSymbol << "   |   ";
        cout << "q[";
        for (size_t i = 0; i < transition.nextStates.size(); ++i) {
            cout << transition.nextStates[i];
            if (i < transition.nextStates.size() - 1)
                cout << "], q[";
        }
        cout << "]\n";
    }
    cout << "_________________________________________\n";

    // Convert NFA to DFA
    convertNFAtoDFA();

    // DFA transition table output
    cout << "\n\tDFA Transition Table\n";
    cout << "_________________________________________\n";
    cout << "Current State | Input | Next State\n";
    cout << "_________________________________________\n";
    for (const auto &transition : dfaTransitionTable) {
        cout << "      q[" << transition.currentState << "]      |   "
             << transition.inputSymbol << "   |   q[" << transition.nextState << "]\n";
    }
    cout << "_________________________________________\n";

    return 0;
}
