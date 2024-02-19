//
// Created by Connor Ragland on 2/7/24.
//

#include "AVL.h"

int AVLTree::nodeHeight(TreeNode* node) {  // Referenced from lecture slides
    if (node == nullptr) {
        return 0;
    }
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

bool AVLTree::identicalName(std::string name1, std::string name2) {
    return name1 == name2;
}

string AVLTree::removeQuotations(std::string name) {  // Referenced https://cplusplus.com/reference/cstring/strtok/
    const char* charName = name.c_str();

    char* temp = strtok((char*)charName, "\"");
    if (temp != nullptr) {
        return (string)temp;
    }
    else {
        return "-";  // If empty string
    }
}

bool AVLTree::validName(std::string name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') {  // Only alphabetic or spaces
            return false;
        }
    }
    return true;
}

bool AVLTree::validID(std::string ufid) {
    // Check if 8 characters long and contain only numbers
    return all_of(ufid.begin(), ufid.end(), ::isdigit) && ufid.length() == 8;
}

bool AVLTree::containsID(TreeNode* node, std::string ufid) {
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

bool AVLTree::containsName(TreeNode* node, std::string name) {
    bool result = false;
    if (node == nullptr) {
        result = false;
    }
    else {
        if (identicalName(name, node->name)) {
            return true;
        }

        result = containsName(node->left, name);
        if (result) {
            return true;
        }

        result = containsName(node->right, name);
        if (result) {
            return true;
        }
    }
    return result;
}

int AVLTree::calculateBalance(TreeNode* node) {  // Calculates the balance facter of a particular node
    return node == nullptr ? 0 : (getHeight(node->left) - getHeight((node->right)));
}

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

TreeNode* AVLTree::helperInsert(TreeNode* node, std::string name, std::string ufid) {  // Referenced from slide 28 of balanced trees
    if (containsID(node, ufid)) {  // If already present => don't add
        cout << "unsuccessful" << endl;
        return node;
    }
    name = removeQuotations(name);
    if (!validName(name) || !validID(ufid)) {
        cout << "unsuccessful" << endl;
        return node;
    }
    else {
        if (node == nullptr) {
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

TreeNode* AVLTree::helperRemoveID(TreeNode* node, std::string ufid) {  // Referenced from slide 38 of Trees
    if (!containsID(node, ufid)) {  // If already present => don't add
        cout << "unsuccessful" << endl;
        return node;
    }
    if (node == nullptr) {
        return node;
    }
    if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
        node->left = helperRemoveID(node->left, ufid);
        return node;
    }
    if (compareID(ufid, node->ufid) > 0) {  // ufid1 > ufid2
        node->right = helperRemoveID(node->right, ufid);
        return node;
    }

    if (node->left == nullptr && node->right == nullptr) {  // No children case
        delete node;
        cout << "successful" << endl;
        return nullptr;
    }
    else if (node->left == nullptr) {  // One right child case
        TreeNode* temp = node->right;
        delete node;
        cout << "successful" << endl;
        return temp;
    }
    else if (node->right == nullptr) {  // One left child case
        TreeNode* temp = node->left;
        delete node;
        cout << "successful" << endl;
        return temp;
    }
    else {  // Two children case
        TreeNode* parent = node;

        // Find leftmost node in the right subtree
        TreeNode* current = node->right;
        while (current->left != nullptr) {
            parent = current;
            current = current->left;
        }

        if (parent != node) {
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }

        node->name = current->name;
        node->ufid = current->ufid;

        delete current;
        cout << "successful" << endl;
        return node;
    }
}

void AVLTree::helperSearchID(TreeNode* node, std::string ufid) {
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
    }
    else if (compareID(ufid, node->ufid) == 0) {
        cout << node->name << endl;
    }
    else {
        if (compareID(ufid, node->ufid) < 0) {
            helperSearchID(node->left, ufid);
        }
        else {
            helperSearchID(node->right, ufid);
        }
    }
}

void AVLTree::helperSearchName(TreeNode* node, std::string name) {  // Need to search through whole tree to find all names.
    if (node == nullptr) {
        cout << "";
    }
    else {
        if (identicalName(node->name, name)) {
            cout << node->ufid << endl;
        }
        helperSearchName(node->left, name);
        helperSearchName(node->right, name);
    }
}

void AVLTree::helperInorder(TreeNode* node) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        helperInorder(node->left);
        cout << node->name << ", ";
        helperInorder(node->right);
    }
}

void AVLTree::vectorInorder(TreeNode* node, vector<string> &ufidVector) {
    if (node != nullptr) {
        vectorInorder(node->left, ufidVector);
        ufidVector.push_back(node->ufid);
        vectorInorder(node->right, ufidVector);
    }
}

void AVLTree::helperPreorder(TreeNode* node) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        cout << node->name << " ";
        helperPreorder(node->left);
        helperPreorder(node->right);
    }
}

void AVLTree::helperPostorder(TreeNode* node) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        helperPostorder(node->left);
        helperPostorder(node->right);
        cout << node->name << " ";
    }
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
    helperInorder(this->root);
}

void AVLTree::printPreorder() {
    helperPreorder(this->root);
}

void AVLTree::printPostorder() {
    helperPostorder(this->root);
}

void AVLTree::printLevelCount() {
    if (this->root == nullptr) {
        cout << 0;
    }
    else {
        cout << this->root->height << endl;
    }
}

void AVLTree::removeInorder(int n) {
    vector<string> ufidVector;
    vectorInorder(this->root, ufidVector);
    if (ufidVector.size()-1 < n) {
        cout << "unsuccessful" << endl;
    }
    else {
        removeID(ufidVector.at(n));
    }
}