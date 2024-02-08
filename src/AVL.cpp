//
// Created by Connor Ragland on 2/7/24.
//

#include "AVL.h"

int AVLTree::nodeHeight(TreeNode* node) {
    return 1 + std::max(node->left == nullptr ? 0 : node->left->height, node->right == nullptr ? 0 : node->right->height);
}

int AVLTree::compareID(std::string ufid1, std::string ufid2) {
    // < 0 : ufid1 < ufid2
    // = 0 : ufid1 = ufid2
    // > 0 : ufid1 > ufid2
    return ufid1.compare(ufid2);
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

TreeNode* AVLTree::helperInsert(TreeNode* node, std::string name, std::string ufid) {
    name = removeQuotations(name);
    if (!validName(name) || !validID(ufid)) {
        cout << "Unsuccessful" << endl;
    }
    else {
        if (node == nullptr) {
            return new TreeNode(name, ufid);
        }
        else if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
            node->left = helperInsert(node->left, name, ufid);
        }
        else if (compareID(ufid, node->ufid) == 0) {  //TODO: Fix errors with inserting duplicates. Heights not calculating properly.
            cout << "Unsuccessful" << endl;
        }
        else {  // > 0 : ufid1 > ufid2
            node->right = helperInsert(node->right, name, ufid);
        }
    }

    node->height = nodeHeight(node);  // Referenced from lecture slides

    //TODO: balance

    return node;
}

void AVLTree::helperInorder(TreeNode* node) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        helperInorder(node->left);
//        cout << node->name << " ";
//        cout << node->height << " ";
        helperInorder(node->right);
    }
}

void AVLTree::insert(std::string name, std::string ufid) {
    this->root = helperInsert(this->root, name, ufid);
}

void AVLTree::inorder() {
    helperInorder(this->root);
}