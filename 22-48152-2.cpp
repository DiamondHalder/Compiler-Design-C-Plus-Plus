#include <iostream>
#include <sstream>
#include <set>
#include <regex>
#include <fstream>

using namespace std;

// Function to check if a token is a keyword
bool isKeyword(const string& token) {
    // List of keywords in C++
    const string keywords[] = {
        "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto",
        "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class", "compl",
        "concept", "const", "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return",
        "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit",
        "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable",
        "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
        "public", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static",
        "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local",
        "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void",
        "volatile", "wchar_t", "while", "xor", "xor_eq","cout","cin"
    };

    for (const string& kw : keywords) {
        if (token == kw) {
            return true;
        }
    }
    return false;
}

// Function to check if a token is an operator
bool isOperator(const string& token) {
    // List of operators in C++
    const string operators[] = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~",
        "<<", ">>", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "++", "--", "->", "::"
    };

    for (const string& op : operators) {
        if (token == op) {
            return true;
        }
    }
    return false;
}

// Function to check if a character is punctuation
bool isPunctuation(char ch) {
    // List of punctuation characters in C++
    const char punctuations[] = { '{', '}', '[', ']', '(', ')', ';', ',', '.', ':', '?', '*', '&' };
    for (char p : punctuations) {
        if (ch == p) {
            return true;
        }
    }
    return false;
}

// Function to check if a token is a number
bool isNumber(const string& token) {
    return regex_match(token, regex("[0-9]+"));
}

// Function to analyze the code
void analyzeCode(const string& code) {
    stringstream ss(code);
    string token;

    // Use sets to avoid duplicates
    set<string> keywords, identifiers, operators, punctuations;

    // Process the input code
    while (ss >> token) {
        string cleanToken;

        for (char ch : token) {
            if (isPunctuation(ch)) {
                punctuations.insert(string(1, ch));
            } else {
                cleanToken += ch;
            }
        }

        if (isKeyword(cleanToken)) {
            keywords.insert(cleanToken);
        } else if (isOperator(cleanToken)) {
            operators.insert(cleanToken);
        } else if (!isNumber(cleanToken) && !cleanToken.empty()) {
            identifiers.insert(cleanToken);
        }
    }

    // Display the categorized tokens
    cout << "Keywords: ";
    for (const string& kw : keywords) cout << kw << " ";
    cout << "\nIdentifiers: ";
    for (const string& id : identifiers) cout << id << " ";
    cout << "\nOperators: ";
    for (const string& op : operators) cout << op << " ";
    cout << "\nPunctuations: ";
    for (const string& punc : punctuations) cout << punc << " ";
}

int main() {
    string code;
    string line;


    ifstream file("D://DIAMOND//BSc//SEMESTER 8//COMPILER DESIGN//Operators.txt");





    while (getline(file, line)) {
       code += line + "\n";
       //cout<<line<<endl;
    }

    file.close();


    analyzeCode(code);

    return 0;
}

