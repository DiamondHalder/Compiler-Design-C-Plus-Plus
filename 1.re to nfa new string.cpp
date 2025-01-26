#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Transition {
    int currentState;
    char inputSymbol;
    vector<int> nextStates;
};

int main() {

    string regex;
    cout << "Enter the regular expression : ";
    cin >> regex;

    if (regex != "(0|1)*11*") {
        cout << "Invalid regular expression. This program only works for (0|1)*11*." << endl;
        return 1;
    }

    cout << "Given regular expression: " << regex << endl;

    vector<Transition> transitionTable;

    // Transitions for (0|1)*11*
    transitionTable.push_back({0, 'e', {1, 6}});
    transitionTable.push_back({1, 'e', {2,4}});
    transitionTable.push_back({2, '0', {3}});
    transitionTable.push_back({3, 'e', {1,6}});
    transitionTable.push_back({4, '1', {5}});
    transitionTable.push_back({5, 'e', {1,6}});
    transitionTable.push_back({6, 'e', {7}});
    transitionTable.push_back({7, '1', {8}});
    transitionTable.push_back({8, 'e', {9}});
    transitionTable.push_back({9, 'e', {10}});
    transitionTable.push_back({10, '1', {11}});
     transitionTable.push_back({11, '1', {10}});

    cout << "\n\tTransition Table\n";
    cout << "_________________________________________\n";
    cout << "Current State   | Input | Next States\n";
    cout << "_________________________________________\n";

    for (const auto &transition : transitionTable) {
        cout << "      q[" << transition.currentState << "]        |     "
             << transition.inputSymbol << "     |   ";
        cout << "q[";
        for (size_t i = 0; i < transition.nextStates.size(); ++i) {
            cout << transition.nextStates[i];
            if (i < transition.nextStates.size() - 1)
                cout << "], q[";
        }
        cout << "]\n";
    }

    cout << "_________________________________________\n";

    return 0;
}

