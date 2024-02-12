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

TreeNode* AVLTree::helperInsert(TreeNode* node, std::string name, std::string ufid) {
    if (containsID(node, ufid)) {  // If already present => don't add
        cout << "Unsuccessful" << endl;
        return node;
    }
    name = removeQuotations(name);
    if (!validName(name) || !validID(ufid)) {
        cout << "Unsuccessful" << endl;
        return node;
    }
    else {
        if (node == nullptr) {

            node = new TreeNode(name, ufid);
        }
        else if (compareID(ufid, node->ufid) < 0) {  // ufid1 < ufid2
            node->left = helperInsert(node->left, name, ufid);
        }
        else {  // > 0 : ufid1 > ufid2
            node->right = helperInsert(node->right, name, ufid);
        }
    }

    node->height = nodeHeight(node);  // Referenced from lecture slides

    //TODO: balance

    return node;
}

void AVLTree::helperRemoveID(TreeNode* node, std::string ufid) {
    // TODO: Check valid id?
    if (node == nullptr) {
        cout << "Unsuccessful" << endl;
    }
    else if (compareID(ufid, node->ufid) == 0) {
        cout << "Successful" << endl;
        // TODO: Remove that node and re link nodes
    }
    else {
        if (compareID(ufid, node->ufid) < 0) {
            helperRemoveID(node->left, ufid);
        }
        else {
            helperRemoveID(node->right, ufid);
        }
    }
}

void AVLTree::helperSearchID(TreeNode* node, std::string ufid) {
    // TODO: Check valid id?
    if (node == nullptr) {
        cout << "Unsuccessful" << endl;
    }
    else if (compareID(ufid, node->ufid) == 0) {
        cout << node->name << endl;
        cout << "Successful" << endl;
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

//void AVLTree::helperSearchName(TreeNode* node, std::string name) {  // Need to search through whole tree to find all names.
//
//}

void AVLTree::helperInorder(TreeNode* node) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        helperInorder(node->left);
        cout << node->name << " ";
//        cout << node->height << " ";
        helperInorder(node->right);
    }
}

void AVLTree::helperPreorder(TreeNode *node) {
    if (node == nullptr) {
        cout << "";
    }
    else {
        cout << node->name << " ";
        helperPreorder(node->left);
        helperPreorder(node->right);
    }
}

void AVLTree::helperPostorder(TreeNode *node) {
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
    helperRemoveID(this->root, ufid);
}

void AVLTree::searchID(std::string ufid) {
    helperSearchID(this->root, ufid);
}

//void AVLTree::searchName(std::string name) {
//    helperSearchName(this->root, name);
//}

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