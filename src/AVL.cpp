//
// Created by Connor Ragland on 2/7/24.
//

#include "AVL.h"

int AVLTree::nodeHeight(TreeNode* node) {  // Referenced from lecture slides
    return 1 + std::max(node->left == nullptr ? 0 : node->left->height, node->right == nullptr ? 0 : node->right->height);
}

int AVLTree::getHeight(TreeNode *node) {  // Returns height of a particular node (one based)
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::compareID(std::string ufid1, std::string ufid2) {
    // < 0 : ufid1 < ufid2
    // = 0 : ufid1 = ufid2
    // > 0 : ufid1 > ufid2
    return ufid1.compare(ufid2);
}

bool AVLTree::identicalName(std::string name1, std::string name2) {  // Returns a bool on whether the name is identical or not
    return name1 == name2;
}

string AVLTree::removeQuotations(std::string name) {  // Removes the quotations from as tring
    const char* charName = name.c_str();
    // Referenced https://cplusplus.com/reference/cstring/strtok/
    char* temp = strtok((char*)charName, "\"");
    if (temp != nullptr) {
        return (string)temp;
    }
    else {
        return "-";  // If empty string
    }
}

bool AVLTree::validName(std::string name) {  // Returns if a name is valid
    if (name[0] != '"') {  // If there is no leading quotation, it is not a name.
        return false;
    }
    name = removeQuotations(name);  // Remove quotations
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') {  // Only alphabetic or spaces
            return false;
        }
    }
    return true;
}

bool AVLTree::validID(std::string ufid) {  // Check if 8 characters long and contain only numbers
    for (char c : ufid) {
        if (!isdigit(c)) {
            return false;
        }
    }
    if (ufid.length() != 8) {
        return false;
    }
    return true;
}

bool AVLTree::containsID(TreeNode* node, std::string ufid) {  // Checks if the tree contains a node with the corresponding UFID
    bool result = false;
    if (node == nullptr) {
        result = false;
    }
    else if (compareID(ufid, node->ufid) == 0) {
        result = true;
    }
    else {
        if (compareID(ufid, node->ufid) < 0) {
            result = containsID(node->left, ufid);
        } else {
            result = containsID(node->right, ufid);
        }
    }
    return result;
}

bool AVLTree::containsName(TreeNode* node, std::string name) {  // Checks if the tree contains a node with the corresponding name
    if (node == nullptr) {
        return false;
    }
    if (identicalName(name, node->name)) {
        return true;
    }
    if (containsName(node->left, name)) {
        return true;
    }
    if (containsName(node->right, name)) {
        return true;
    }
    return false;
}

int AVLTree::calculateBalance(TreeNode* node) {  // Calculates the balance facter of a particular node
    return node == nullptr ? 0 : (getHeight(node->left) - getHeight((node->right)));
}

// Referenced Stepik solutions and the logic in the lecture slides/project overview slides
TreeNode* AVLTree::rotateLeft(TreeNode* node) {  // node = the root of the rotation
    TreeNode* rightChild = node->right;
    TreeNode* rightChildLeftSubtree = rightChild->left;

    // Rotate
    rightChild->left = node;
    node->right = rightChildLeftSubtree;

    // Update heights of both nodes
    node->height = nodeHeight(node);
    rightChild->height = nodeHeight(rightChild);

    // rightChild is now the root of that subtree
    return rightChild;
}

// Referenced Stepik solutions and the logic in the lecture slides/project overview slides
TreeNode* AVLTree::rotateRight(TreeNode* node) {  // node = root of rotation
    TreeNode* leftChild = node->left;
    TreeNode* leftChildRightSubtree = leftChild->right;

    // Rotate
    leftChild->right = node;
    node->left = leftChildRightSubtree;

    // Update heights of both nodes
    node->height = nodeHeight(node);
    leftChild->height = nodeHeight(leftChild);

    // leftChild is now the root of that subtree
    return leftChild;
}

TreeNode* AVLTree::rotateLeftRight(TreeNode* node) {  // node = root of rotation
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

TreeNode* AVLTree::rotateRightLeft(TreeNode* node) {  // node = root of rotation
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// Referenced from slide 28 of balanced trees
TreeNode* AVLTree::helperInsert(TreeNode* node, std::string name, std::string ufid) {
    name = removeQuotations(name);
    if (node == nullptr) {
        this->nodeCount++;  // Increment nodeCount in tree class
        cout << "successful" << endl;
        return new TreeNode(name, ufid);
    }
    if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
        node->left = helperInsert(node->left, name, ufid);
    }
    else if (compareID(ufid, node->ufid) == 0) {
        cout << "unsuccessful" << endl;
        return node;
    }
    else {  // > 0 : ufid1 > ufid2
        node->right = helperInsert(node->right, name, ufid);
    }

    node->height = nodeHeight(node);

    int balanceFactor = calculateBalance(node);

    if (balanceFactor > 1 && ufid < node->left->ufid) {  // Left left case
        return rotateRight(node);
    }
    if (balanceFactor < -1 && ufid > node->right->ufid) {  // Right right case
        return rotateLeft(node);
    }
    if (balanceFactor > 1 && ufid > node->left->ufid) {  // Left right case
        return rotateLeftRight(node);
    }
    if (balanceFactor < -1 && ufid < node->right->ufid) {  // Right left case
        return rotateRightLeft(node);
    }

    return node;
}

// Referenced from slide 38 of Trees
TreeNode* AVLTree::helperRemoveID(TreeNode* node, std::string ufid) {
    if (!containsID(node, ufid)) {  // If not in tree => unsuccessful
        cout << "unsuccessful" << endl;
        return node;
    }
    if (node == nullptr) {
        return node;
    }
    if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
        node->left = helperRemoveID(node->left, ufid);
    }
    else if (compareID(ufid, node->ufid) > 0) {  // ufid1 > ufid2
        node->right = helperRemoveID(node->right, ufid);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {  // No children case
            delete node;
            cout << "successful" << endl;
            this->nodeCount--;
            node = nullptr;
        }
        else if (node->left == nullptr) {  // One right child case
            TreeNode* temp = node->right;
            delete node;
            cout << "successful" << endl;
            this->nodeCount--;
            node = temp;
        }
        else if (node->right == nullptr) {  // One left child case
            TreeNode* temp = node->left;
            delete node;
            cout << "successful" << endl;
            this->nodeCount--;
            node = temp;
        }
        else {  // Two children case
            TreeNode* successorParent = node;

            // Find the smallest node in the right subtree (in order successor)
            TreeNode* successor = node->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }
            // Move successors values to the node to be deleted
            node->name = successor->name;
            node->ufid = successor->ufid;

            // Re-attach ndoes where the succcessor used to be
            if (successorParent != node) {
                successorParent->left = successor->right;
            }
            else {
                successorParent->right = successor->right;
            }

            // Delete successor
            node->right = helperRemoveSuccessor(node->right, successor->ufid);
            cout << "successful" << endl;
            this->nodeCount--;
        }
    }

    if (node == nullptr) {  // No nodes left after deleting
        return node;
    }

    // Update heights
    node->height = nodeHeight(node);

    return node;
}

TreeNode* AVLTree::helperRemoveSuccessor(TreeNode *node, std::string ufid) {
    if (node == nullptr) {
        return node;
    }
    if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
        node->left = helperRemoveSuccessor(node->left, ufid);
    }
    else if (compareID(ufid, node->ufid) > 0) {  // ufid1 > ufid2
        node->right = helperRemoveSuccessor(node->right, ufid);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {  // No children case
            delete node;
            this->nodeCount--;
            node = nullptr;
        }
        else if (node->left == nullptr) {  // One right child case
            TreeNode* temp = node->right;
            delete node;
            this->nodeCount--;
            node = temp;
        }
        else if (node->right == nullptr) {  // One left child case
            TreeNode* temp = node->left;
            delete node;
            this->nodeCount--;
            node = temp;
        }
        else {  // Two children case
            TreeNode* successorParent = node;

            // Find the smallest node in the right subtree (in order successor)
            TreeNode* successor = node->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }
            // Swap values
            node->name = successor->name;
            node->ufid = successor->ufid;

            if (successorParent != node) {
                successorParent->left = successor->right;
            }
            else {
                successorParent->right = successor->right;
            }

            // Remove successor
            node->right = helperRemoveSuccessor(node->right, successor->ufid);
            this->nodeCount--;
        }
    }

    if (node == nullptr) {  // No nodes left after deleting
        return node;
    }

    // Update heights
    node->height = nodeHeight(node);

    return node;
}

void AVLTree::helperSearchID(TreeNode* node, std::string ufid) {
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
    }
    else if (compareID(ufid, node->ufid) == 0) {  // Print name if found
        cout << node->name << endl;
    }
    else {
        if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
            helperSearchID(node->left, ufid);
        }
        else {  // ufid1 > ufid2
            helperSearchID(node->right, ufid);
        }
    }
}

void AVLTree::helperSearchName(TreeNode* node, std::string name) {  // Need to search through whole tree to find all names.
    if (node == nullptr) {
        cout << "";
    }
    else {
        if (identicalName(node->name, name)) {  // If identical print the ufid
            cout << node->ufid << endl;
        }
        helperSearchName(node->left, name);  // Search left
        helperSearchName(node->right, name);  // Search right
    }
}

void AVLTree::helperInorder(TreeNode* node, int& count) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        helperInorder(node->left, count);
        cout << node->name;
        count++;
        if (count != this->nodeCount) {
            cout << ", ";
        }
        helperInorder(node->right, count);
    }
}

void AVLTree::vectorInorder(TreeNode* node, vector<string> &ufidVector) {
    if (node != nullptr) {
        vectorInorder(node->left, ufidVector);
        ufidVector.push_back(node->ufid);
        vectorInorder(node->right, ufidVector);
    }
}

void AVLTree::helperPreorder(TreeNode* node, int& count) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        count++;
        cout << node->name;
        if (count != this->nodeCount) {
            cout << ", ";
        }
        helperPreorder(node->left, count);
        helperPreorder(node->right, count);
    }
}

void AVLTree::helperPostorder(TreeNode* node, int& count) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        helperPostorder(node->left, count);
        helperPostorder(node->right, count);
        count++;
        cout << node->name;
        if (count != this->nodeCount) {
            cout << ", ";
        }
    }
}

bool AVLTree::helperSearchCommand(std::string token) {  // Checks if the input is a name or a ufid
    if (!validID(token)) {  // If not a valid id it is possibly a name
        return true;
    }
    return false;
}

vector<string> AVLTree::parseInputs(std::string input) {  // Parse inputs from one line of a command.
    stringstream ss(input);
    vector<string> parsed;
    bool quote = false;

    string item;
    while (ss >> item) {
        if (item.front() == '"' && item.back() == '"') {  // Check if one item of a string is one word in quotations
            if (item == "\"" && quote) {  // If last item is just the quote, there will be a space before
                parsed.back() += " " + item;
                quote = false;
            }
            else {
                parsed.push_back(item);
            }
        }
        else if (item.front() == '"') {  // If starts with quotation but doesn't finish
            parsed.push_back(item);
            quote = true;
        }
        else if (item.back() == '"') {  // Final part of a quotation wrapped name
            quote = false;
            if (!parsed.empty()) {
                parsed.back() += " " + item;
            }
            else {
                parsed.push_back(item);
            }
        }
        else if (quote) {
            parsed.back() += " " + item;  // Middle part of a quotation wrapped name with spaces
        }
        else {  // Non " " case
            parsed.push_back(item);
        }
    }

    return parsed;
}

void AVLTree::executeCommands(vector<std::string> commands) {  // Where the commands are executed after being parsed.
    if (commands[0] == "insert") {
        if (!validName(commands[1]) || !validID(commands[2]) || commands.size() != 3) {  // Check valid insert
            cout << "unsuccessful" << endl;
        }
        else {
            insert(removeQuotations(commands[1]), commands[2]);
        }
    }
    else if (commands[0] == "remove") {  // Removes by UFID
        if (!validID(commands[1])) {
            cout << "unsuccessful" << endl;
        }
        else {
            removeID(commands[1]);
        }
    }
    else if (commands[0] == "search") {
        // If quotations => name
        // If numbers => UFID
        if (helperSearchCommand(removeQuotations(commands[1]))) {  // True = name
            if (validName(commands[1])) {
                searchName(removeQuotations(commands[1]));
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else {  // False = UFID
            if (validID(commands[1])) {
                searchID(commands[1]);
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
    }
    else if (commands[0] == "printInorder") {
        printInorder();
        cout << endl;
    }
    else if (commands[0] == "printPreorder") {
        printPreorder();
        cout << endl;
    }
    else if (commands[0] == "printPostorder") {
        printPostorder();
        cout << endl;
    }
    else if (commands[0] == "printLevelCount") {
        printLevelCount();
    }
    else if (commands[0] == "removeInorder") {
        int idx = stoi(commands[1]);
        if (idx < 0) {
            cout << "unsuccessful" << endl;
        }
        else {
            if (removeInorder(idx)) {
            }
        }
    }
    else {  // If command is invalid
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::command(std::string commandLine) {  // Public function for the user to enter the command in
    vector<string> commands = parseInputs(commandLine);
    executeCommands(commands);
}

void AVLTree::insert(std::string name, std::string ufid) {
    this->root = helperInsert(this->root, name, ufid);
}

void AVLTree::removeID(std::string ufid) {
    this->root = helperRemoveID(this->root, ufid);
}

void AVLTree::searchID(std::string ufid) {
    helperSearchID(this->root, ufid);
}

void AVLTree::searchName(std::string name) {
    if (!containsName(this->root, name)) {
        cout << "unsuccessful" << endl;
    }
    else {
        helperSearchName(this->root, name);
    }
}

void AVLTree::printInorder() {
    int count = 0;
    helperInorder(this->root, count);
}

void AVLTree::printPreorder() {
    int count = 0;
    helperPreorder(this->root, count);
}

void AVLTree::printPostorder() {
    int count = 0;
    helperPostorder(this->root, count);
}

void AVLTree::printLevelCount() {
    if (this->root == nullptr) {
        cout << 0 << endl;
    }
    else {
        cout << this->root->height << endl;
    }
}

bool AVLTree::removeInorder(int n) {
    if (this->root == nullptr) {
        cout << "unsuccessful" << endl;
        return false;
    }
    vector<string> ufidVector;
    vectorInorder(this->root, ufidVector);  // Add all nodes from tree into a vector in-order
    if (ufidVector.size()-1 < n) {
        cout << "unsuccessful" << endl;
        return false;
    }
    else {
        removeID(ufidVector.at(n));
    }
    return true;
}