#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function to trim leading and trailing whitespaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to check if a function is valid
bool isValidFunction(const string& code) {
    string returnType, functionName, functionBody;
    bool inBody = false;

    istringstream stream(code);
    string line;

    while (getline(stream, line)) {
        line = trim(line);

        // Detect the function header
        if (!inBody && line.find('{') != string::npos) {
            // Extract the return type and function name
            size_t parenPos = line.find('(');
            size_t bracePos = line.find('{');
            if (parenPos != string::npos && bracePos != string::npos && parenPos < bracePos) {
                size_t firstSpace = line.find(' ');
                if (firstSpace != string::npos) {
                    returnType = line.substr(0, firstSpace);
                    functionName = line.substr(firstSpace + 1, parenPos - firstSpace - 1);
                    inBody = true; // Start parsing the body
                }
            }
        } else if (inBody) {
            // Collect function body until closing brace is found
            if (line.find('}') != string::npos) {
                inBody = false;
            } else {
                functionBody += line + " ";
            }
        }
    }

    // Validate the function based on return type
    if (returnType == "void") {
        // Void functions should not have a "return" statement
        return functionBody.find("return") == string::npos;
    } else {
        // Non-void functions must have at least one "return" statement
        return functionBody.find("return") != string::npos;
    }
}

int main() {
    string filePath = "D:\\DIAMOND\\BSc\\SEMESTER 8\\COMPILER DESIGN\\FunctionCheck.txt";
    ifstream inputFile(filePath);

    if (!inputFile) {
        cerr << "Error: Unable to open file at " << filePath << endl;
        return 1;
    }

    // Read the entire content of the file
    string code((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    if (isValidFunction(code)) {
        cout << "The function is valid according to the conditions." << endl;
    } else {
        cout << "The function is invalid according to the conditions." << endl;
    }

    return 0;
}
