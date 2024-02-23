#include <iostream>
#include "AVL.h"
#include <string>
using namespace std;

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

int main() {
    AVLTree myAVL;
    int numCommands = 0;
    string commandString;

    cin >> numCommands;
    cin.ignore(); // Referenced: https://cplusplus.com/reference/istream/istream/ignore/

    for (int i = 0; i < numCommands; i++) {
        getline(cin, commandString);  // Take every line as input

        myAVL.command(commandString);
    }

    return 0;
}