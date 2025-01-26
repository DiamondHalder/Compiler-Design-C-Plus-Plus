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


    if (regex != "(a|b)*") {
        cout << "Invalid regular expression. This program only works for (a|b)*." << endl;
        return 1;
    }

    cout << "Given regular expression: " << regex << endl;


    vector<Transition> transitionTable;


    transitionTable.push_back({0, 'e', {6, 7}});


    transitionTable.push_back({1, 'a', {2}});
    transitionTable.push_back({2, 'e', {5}});


    transitionTable.push_back({3, 'b', { 4}});


    transitionTable.push_back({4, 'e', {5}});


    transitionTable.push_back({5, 'e', {6, 7}});


    transitionTable.push_back({6, 'e', {1, 3}});


    cout << "\n\tTransition Table\n";
    cout << "_________________________________________\n";
    cout << "Current State | Input | Next States\n";
    cout << "_________________________________________\n";

    for (const auto &transition : transitionTable) {
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

    return 0;
}
