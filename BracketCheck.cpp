#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

bool areBracketsBalanced(const std::string& equation, string& missingBracketInfo) {
    std::stack<int> brackets;  // Stack to store the positions of opening brackets

    for (int i = 0; i < equation.size(); i++) {
        char ch = equation[i];

        if (ch == '(') {
            brackets.push(i);  // Push the position of the opening bracket
        } else if (ch == ')') {
            if (brackets.empty()) {
                missingBracketInfo = "Closing bracket at position " + to_string(i) + " has no matching opening bracket.";
                return false;  // No matching opening bracket
            }
            brackets.pop();  // Pop the top of the stack if a matching closing bracket is found
        }
    }

    if (!brackets.empty()) {
        int missingPosition = brackets.top();
        missingBracketInfo = "Opening bracket at position " + to_string(missingPosition) + " has no matching closing bracket.";
        return false;  // There's an unmatched opening bracket
    }

    return true;
}

int main() {
    std::ifstream file("D:\\DIAMOND\\BSc\\SEMESTER 8\\COMPILER DESIGN\\Equetion.txt");
    if (!file) {
        std::cerr << "Error opening file!";
        return 1;
    }

    std::string equation;
    std::getline(file, equation);  // Read the entire line from the file
    file.close();

    string missingBracketInfo;
    cout << "Equation: " << equation << endl;

    if (areBracketsBalanced(equation, missingBracketInfo)) {
        cout << "The brackets in the equation are balanced.\n";
    } else {
        cout << "The brackets in the equation are not balanced.\n";
        cout << "Reason: " << missingBracketInfo << endl;
    }

    return 0;
}
