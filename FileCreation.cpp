#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string myText;

    // Open the existing text file for reading
    ifstream MyReadFile("D://DIAMOND//BSc//SEMESTER 8//COMPILER DESIGN//test.txt");

    // Check if the file opened successfully


    // Read the file line by line
    while (getline(MyReadFile, myText))
    {
        // Output each line from the file
        cout << myText << endl;
    }

    // Close the file
    MyReadFile.close();

    return 0;
}
