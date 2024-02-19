#include <iostream>
#include "AVL.h"
#include <vector>
#include <sstream>
#include <string>
using namespace std;

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

string removeQuotations(string name) {  // Referenced https://cplusplus.com/reference/cstring/strtok/
    const char* charName = name.c_str();

    char* temp = strtok((char*)charName, "\"");
    if (temp != nullptr) {
        return (string)temp;
    }
    else {
        return "-";  // If empty string
    }
}

vector<string> parseInput(std::string input) {
    stringstream ss(input);
    vector<string> parsed;

    string item;
    while (ss >> item) {
        parsed.push_back(item);
    }

    return parsed;
}

bool validName(std::string name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') {  // Only alphabetic or spaces
            return false;
        }
    }
    return true;
}

bool validID(std::string ufid) {
    // Check if 8 characters long and contain only numbers
    return all_of(ufid.begin(), ufid.end(), ::isdigit) && ufid.length() == 8;
}

bool helperSearch(std::string token) {  // Returns true if name and false if UFID
    if (!validID(token)) {  // If not a valid id it is possibly a name
        return true;
    }
    return false;
}

void printSuccessful() {
    cout << "successful" << endl;
}

void printUnsuccessful() {
    cout << "unsuccessful" << endl;
}

int main() {
    AVLTree myAVL;
    int numCommands = 0;
    string commandString;
    vector<string> commands;

    cout << "Input number of commands: ";
    cin >> numCommands;
    cin.ignore(); // Referenced: https://cplusplus.com/reference/istream/istream/ignore/

    for (int i = 0; i < numCommands; i++) {
        getline(cin, commandString);

        commands = parseInput(commandString);

//        for (const auto& token : commands) {
//            cout << token << " ";
//        }
//        cout << endl;
        if (commands[0] == "insert") {
            if (!validName(removeQuotations(commands[1])) || !validID(commands[2]) || commands.size() != 3) {
                printUnsuccessful();
            }
            else {
                myAVL.insert(removeQuotations(commands[1]), commands[2]);
                printSuccessful();
            }
        }
        else if (commands[0] == "remove") {  // Removes by UFID
            if (!validID(commands[1])) {
                printUnsuccessful();
            }
            else {
                myAVL.removeID(commands[1]);
            }
        }
        else if (commands[0] == "search") {
            // If quotations => name
            // If numbers => UFID
            if (helperSearch(removeQuotations(commands[1]))) {  // True = name
                commands[1] = removeQuotations(commands[1]);
                if (validName(commands[1])) {
                    myAVL.searchName(commands[1]);
                }
                else {
                    printUnsuccessful();
                }
            }
            else {  // False = UFID
                if (validID(commands[1])) {
                    myAVL.searchID(commands[1]);
                }
                else {
                    printUnsuccessful();
                }
            }
        }
        else if (commands[0] == "printInorder") {  // TODO: fix printing without commas
            myAVL.printInorder();
            cout << endl;
        }
        else if (commands[0] == "printPreorder") {
            myAVL.printPreorder();
            cout << endl;
        }
        else if (commands[0] == "printPostorder") {
            myAVL.printPostorder();
            cout << endl;
        }
        else if (commands[0] == "printLevelCount") {
            myAVL.printLevelCount();
        }
        else if (commands[0] == "removeInorder") {
            int idx = stoi(commands[1]);
            if (idx < 0) {
                printUnsuccessful();
            }
            else {
                myAVL.removeInorder(idx);
                printSuccessful();
            }
        }
        else {
            printUnsuccessful();
        }
    }



    return 0;
}