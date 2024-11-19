#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    string filePath = "D:\\DIAMOND\\BSc\\SEMESTER 8\\COMPILER DESIGN\\SemiClone.txt";


    ifstream file(filePath);

    // Check if the file opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;
    bool insideBrackets = false;  // Track if inside curly brackets
    bool allLinesHaveSemicolon = true;

    // Read the file line by line
    while (getline(file, line)) {
        lineNumber++;

        // Check if we encounter an opening curly bracket
        if (line.find('{') != string::npos) {
            insideBrackets = true;
            continue; // Skip the line containing the opening curly bracket
        }

        // Check if we encounter a closing curly bracket
        if (line.find('}') != string::npos) {
            insideBrackets = false;
            continue; // Skip the line containing the closing curly bracket
        }

        // If inside the curly brackets, check for semicolon
        if (insideBrackets && line.find(';') == string::npos) {
            // If no semicolon is found, output the line number and content
            cout << "Line " << lineNumber << " is missing a semicolon: " << line << endl;
            allLinesHaveSemicolon = false;
        }
    }

    // Close the file
    file.close();

    // If all lines within curly brackets have semicolons, report the code as correct
    if (allLinesHaveSemicolon) {
        cout << "The code is correct (all lines within curly brackets contain a semicolon)." << endl;
    } else {
        cout << "The code is not correct (some lines within curly brackets are missing semicolons)." << endl;
    }

    return 0;
}
