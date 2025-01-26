#include <iostream>
#include <string>
#include <regex>

using namespace std;


string processEpsilonInRegex(const string& regexPattern) {
    string processedPattern = regexPattern;


    size_t pos = 0;
    while ((pos = processedPattern.find("e", pos)) != string::npos) {

        if ((pos == 0 || !isalnum(processedPattern[pos - 1])) &&
            (pos == processedPattern.size() - 1 || !isalnum(processedPattern[pos + 1]))) {
            processedPattern.replace(pos, 1, "");
        } else {
            ++pos;
        }
    }

    return processedPattern;
}


void checkRegexMatch(const string& regexPattern, const string& inputString) {
    try {

        string processedPattern = processEpsilonInRegex(regexPattern);


        regex reg(processedPattern);


        if (inputString == "e") {
            if (regex_match("", reg)) {
                cout << "\nThe text matches the regular expression (interpreted epsilon)." << endl;
            } else {
                cout << "\nThe text doesn't match the regular expression." << endl;
            }
            return;
        }


        if (regex_match(inputString, reg)) {
            cout << "\nThe text matches the regular expression." << endl;
        } else {
            cout << "\nThe text doesn't match the regular expression." << endl;
        }
    } catch (const regex_error& e) {
        cout << "\nInvalid regular expression: " << e.what() << endl;
    }
}

int main() {
    string regexPattern, inputString;
    char choice;

    do {

        cout << "\nEnter the regular expression (use 'e' for epsilon): ";
        getline(cin, regexPattern);


        cout << "Enter the text: ";
        getline(cin, inputString);


        checkRegexMatch(regexPattern, inputString);


        cout << "\nDo you want to continue? (Y/N): ";
        cin >> choice;
        cin.ignore();

    } while (choice == 'Y' || choice == 'y');

    return 0;
}
