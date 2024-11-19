
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // Create and open a text file
    ofstream MyFile;
    MyFile.open("NewFile.txt");

    // Write to the file
    MyFile << "Student information : ";
    MyFile<<"\nName   DEPT     CGPA  \n";
     MyFile <<"\njohn   CSE      4\n";
      MyFile <<"\nSmith  CSE      3.90";

    // Close the file
    MyFile.close();

    string myText;

    // Read from the text file
    //ifstream MyReadFile("C://Users//Teacher//Desktop//Fall-24-25//Compiler Design//New folder//LAB//Lab 1//Lab-1 Codes//student.txt");
    ifstream MyReadFile("NewFile.txt");
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText))
    {
        // Output the text from the file
        cout << myText<<endl;
    }

    // Close the file
    MyReadFile.close();

}

