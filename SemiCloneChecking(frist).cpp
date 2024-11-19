#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Define the path to the file
    string filePath = "D:\\DIAMOND\\BSc\\SEMESTER 8\\COMPILER DESIGN\\SemiClone.txt";

    // Open the file
    ifstream file(filePath);

    // Check if the file opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Variable to store each line of the file
    string line;
    bool hasSemicolon = false;

    // Read the file line by line
    while (getline(file, line)) {
        // Check if the line contains a semicolon
        if (line.find(';') != string::npos) {
            hasSemicolon = true;
            break;
        }
    }

    // Close the file
    file.close();

    // Check the result and output the result
    if (hasSemicolon) {
        cout << "The code is correct (contains semicolon)." << endl;
    } else {
        cout << "The code is not correct (missing semicolon)." << endl;
    }

    return 0;
}

