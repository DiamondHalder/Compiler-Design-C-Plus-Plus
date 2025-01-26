#include <iostream>
#include <string>
using namespace std;

struct Operator {
    int pos;
    char op;
};

string expression;
Operator operators[15];
int operatorCount = 0;
char tempVar = 'A';

void findOperators();
void generateIntermediateCode();
void processLeftOperand(int pos, string &left);
void processRightOperand(int pos, string &right);

int main() {
    cout << "\t\tINTERMEDIATE CODE GENERATION\n\n";
    cout << "Enter the Expression: ";
    cin >> expression;

    cout << "\nThe intermediate code:\n";

    findOperators();
    generateIntermediateCode();

    return 0;
}

void findOperators() {
    string operatorsList = "*/+-";
    int index = 0;
    for (int i = 0; i < expression.length(); i++) {
        char ch = expression[i];
        if (ch == '*' || ch == '/' || ch == '+' || ch == '-') {
            operators[index].pos = i;
            operators[index].op = ch;
            index++;
        }
    }
    operatorCount = index;
}

void generateIntermediateCode() {
    string left, right;
    bool processed[100] = {false};
    int precedenceOrder[4] = {0, 1, 1, 0};

    for (int precedence = 1; precedence >= 0; precedence--) {
        for (int i = 0; i < operatorCount; i++) {
            int pos = operators[i].pos;
            char op = operators[i].op;

            if (processed[pos] || precedenceOrder[op == '*' || op == '/'] != precedence)
                continue;

            processLeftOperand(pos, left);
            processRightOperand(pos, right);

            expression[pos] = tempVar;
            processed[pos] = true;

            cout << "\t" << tempVar << " := " << left << " " << op << " " << right << "\n";
            tempVar++;
        }
    }

    cout << "\tW := " << (char)(tempVar - 1) << "\n";
}

void processLeftOperand(int pos, string &left) {
    left = "";
    for (int i = pos - 1; i >= 0; i--) {
        if (!isalnum(expression[i]) && expression[i] != '$') break;
        if (expression[i] != '$') left = expression[i] + left;
        expression[i] = '$';
    }
}

void processRightOperand(int pos, string &right) {
    right = "";
    for (int i = pos + 1; i < expression.length(); i++) {
        if (!isalnum(expression[i]) && expression[i] != '$') break;
        if (expression[i] != '$') right += expression[i];
        expression[i] = '$';
    }
}
